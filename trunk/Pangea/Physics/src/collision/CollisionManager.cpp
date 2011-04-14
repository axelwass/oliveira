/*
 * CollisionManager.cpp
 *
 *  Created on: Apr 14, 2011
 *      Author: mmerchan
 */

#include "../../include/collision/CollisionManager.h"

void CollisionManager::speculate(real h) {

	// Octree MUST be __outdated__ here, because we need intersections
	// at the initial step!

	/* TODO Note: octree is still behaving wrong, because
	 * octree elements are outdated but the collision shape is updated.
	 * It should be the speculated next position!
	 */

	list<Particle *>::iterator p;
	for (p = particles->begin(); p != particles->end(); p++) {

		list<Positionable<Particle> *>
				closestElements = octree->getIntersectionElements(
						(*p)->getCollisionShape().get());

		// Check possible collisions and speculate
		list<Positionable<Particle> *>::iterator closeP;
		for (closeP = closestElements.begin(); closeP != closestElements.end(); closeP++) {
			Particle * other = (*closeP)->getThis();
			if (other != (*p))
				speculateContact(*p, other, h);
		}

		// Update this particle's final state
		(*p)->integrate(h);
	}

	// Now resolve all collisions
	resolve();

	// And update octree for next integration loop
	octree->update();
}

void CollisionManager::speculateContact(Particle * p1, Particle * p2, real h) {

	// Note on context: we _are_ on final integration step!

	// We get the initial integration data, reposition shapes, intersect, and speculate
	Vector3 initial1 = p1->getIntegrator()->getInitialData()->getPosition();
	ShapePtr s1 = p1->getCollisionShape();
	s1->setPosition(initial1);
	Vector3 initial2 = p2->getIntegrator()->getInitialData()->getPosition();
	ShapePtr s2 = p2->getCollisionShape();
	s2->setPosition(initial2);

	IntersectionData data = s1->intersection(s2.get());

	// Geometric data
	Vector3 normal = data.getNormal();
	Vector3 distance = normal * data.getDistance();

	// Integrator related data
	Vector3 velocity = p1->getIntegrator()->getIntegrationSlope(h)->dx;
	real rkStep = p1->getIntegrator()->getSlopeStep(h);

	real projected = (-1.0) * velocity.scalarProduct(normal);

	// If next step's position is greater than distance, collision occurs!
	if (projected * rkStep >= distance.magnitude()) {

		printf("NEAR COLLISION\n");
		printf("p: %g\n", projected * rkStep);
		printf("d: %g\n", distance.magnitude());

		Vector3 remove = distance;
		remove.normalize();
		remove *= projected - distance.magnitude() * (1.0 / rkStep);
		velocity += remove;

		printf("Remove: %g\n", remove.magnitude() * rkStep);
		printf("post p: %g\n\n", velocity.getY() * rkStep);

		p1->getIntegrator()->getIntegrationSlope(h)->dx = velocity;

		// And now, add this collision event to p1 and p2
		this->add(CollisionEventPtr(new CollisionEvent(p1, p2)));
	}
}

// Adds if it does not already exist
void CollisionManager::add(CollisionEventPtr c) {
	list<CollisionEventPtr>::iterator itr;
	for (itr = collided.begin(); itr != collided.end(); itr++)
		if ((*itr) == c) {

			return;
		}

	collided.push_back(c);
}

void CollisionManager::resolve() {

	list<CollisionEventPtr>::iterator itr;
	for (itr = collided.begin(); itr != collided.end(); itr++) {

		Particle * p1 = (*itr)->p1;
		Particle * p2 = (*itr)->p2;
		IntersectionData data = p1->checkCollision(*p2);
		p1->resolveCollision(*p2, data);

		// Delete this event
		itr = collided.erase(itr);
		itr--;
	}

	octree->update();

}
