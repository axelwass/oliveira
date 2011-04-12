/*
 * ParticleGroup.cpp
 *
 *  Created on: Feb 14, 2011
 *      Author: mmerchan
 */

#include "../../include/particle/ParticleGroup.h"

ParticleGroup::ParticleGroup(const Vector3& emptyPosition, bool selfCollisions) {

	this->selfCollisions = selfCollisions;

	// threshold more than 2 to prevent possible infinite partition due to equal vectors
	octree = OctreePtr(new Octree<Particle> (Vector3(), 10, 2, true));

	boundingShape = SpherePtr(new Sphere(1));
	boundingShape->setPosition(emptyPosition);
}

list<Particle *>& ParticleGroup::getParticles() {
	return particles;
}

int ParticleGroup::getParticleCount() {
	return particles.size();
}

void ParticleGroup::addField(Force * field) {
	this->fields.push_back(field);

	list<Particle *>::iterator itr;
	for (itr = particles.begin(); itr != particles.end(); itr++)
		(*itr)->addForce(field);
}

Particle * ParticleGroup::addParticle(Particle * p) {
	list<Force *>::iterator itr;
	for (itr = fields.begin(); itr != fields.end(); itr++)
		p->addForce(*itr);

	particles.push_back(p);
	if (!octree->put(p))
		printf("Particle octree failed: put\n");
	return p;
}

Particle * ParticleGroup::addParticle(real inverseMass, const Vector3& pos,
		const Vector3& vel) {
	ParticleData data(pos, inverseMass);
	data.setVelocity(vel);
	Particle * p = new Particle(data);

	list<Force *>::iterator itr;
	for (itr = fields.begin(); itr != fields.end(); itr++)
		p->addForce(*itr);

	particles.push_back(p);
	octree->put(p);
	return p;
}

void ParticleGroup::addInternalForce(InterParticleForce * force) {
	list<Particle *>::iterator itr;
	list<Particle *>::iterator itr2;

	for (itr = particles.begin(); itr != particles.end(); itr++)
		for (itr2 = particles.begin(); itr2 != particles.end(); itr2++)
			if ((*itr) != (*itr2)) {
				InterParticleForce * f = force->getFunctionCopy();
				f->setOtherParticle(*itr2);
				(*itr)->addForce(f);
			}
}

Vector3 ParticleGroup::getPosition() {
	return boundingShape->getPosition();
}

ParticleGroup * ParticleGroup::getThis() {
	return this;
}

// Groups must be synchronized with other groups, cannot
// integrate isolated in case of inter-group collisions or interactions
void ParticleGroup::evaluate(real time, real step) {

	this->time = time;
	this->step = step;

	list<Particle *>::iterator itr;

	for (itr = particles.begin(); itr != particles.end(); itr++)
		(*itr)->evaluate(time, step);

}

void ParticleGroup::integrate(real h) {
	list<Particle *>::iterator itr;

	centerOfMass = Vector3();

	// If this step is final integration, speculate collisions
	if (selfCollisions && RK4::getStep() == RK4::getMaxSteps())
		speculateInternalCollisions();

	// Apply step
	for (itr = particles.begin(); itr != particles.end(); itr++) {
		(*itr)->integrate(h);

		// If particle is finite, calculate center of mass
		real inverseMass = (*itr)->getData().getInverseMass();
		if (inverseMass)
			centerOfMass += (*itr)->getPosition() * (1.0 / inverseMass);
	}

	centerOfMass *= (1.0 / particles.size());
	boundingShape->setPosition(centerOfMass);

	real maxRadius = 0;
	for (itr = particles.begin(); itr != particles.end(); itr++) {
		real r = ((*itr)->getPosition() - centerOfMass).magnitude();
		r += 5; // particle radius! jaja
		if (r > maxRadius)
			maxRadius = r;
	}

	boundingShape->setRadius(maxRadius + EPSILON);
}

void ParticleGroup::speculateContact(Particle * p1, Particle * p2) {

	// Note on context: we _are_ on final integration step!

	// We get the initial integration data, reposition shapes, recollide, and speculate
	Vector3 initialPosition =
			p1->getIntegrator()->getInitialData()->getPosition();
	ShapePtr s1 = p1->getCollisionShape();
	s1->setPosition(initialPosition);
	IntersectionData data = s1->intersection(p2->getCollisionShape().get());

	// Geometrical data
	Vector3 normal = data.getNormal();
	Vector3 distance = normal * data.getDistance();

	// Integrator related data
	Vector3 velocity = p1->getIntegrator()->getIntegrationSlope(step)->dx;
	real rkStep = p1->getIntegrator()->getSlopeStep(step);

	real projected = (-1.0) * velocity.scalarProduct(normal);

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

		p1->getIntegrator()->getIntegrationSlope(step)->dx = velocity;
	}
}

// TODO: Note that closest elements is not entirely accurate right now
void ParticleGroup::speculateInternalCollisions() {

	octree->update();

	list<Particle *>::iterator p;
	for (p = particles.begin(); p != particles.end(); p++) {

		list<Positionable<Particle> *>
				closestElements = octree->getIntersectionElements(
						(*p)->getCollisionShape().get());

		list<Positionable<Particle> *>::iterator closeP;
		for (closeP = closestElements.begin(); closeP != closestElements.end(); closeP++) {
			Particle * other = (*closeP)->getThis();
			if (other != (*p))
				speculateContact(*p, other);
		}
	}
}

//Note: we can consider positions being accurate, since it is RK step 1, so data = initialStepData
void ParticleGroup::resolveInternalCollisions() {

	octree->update();

	list<Particle *>::iterator p;
	for (p = particles.begin(); p != particles.end(); p++)
		(*p)->resetCollided();

	for (p = particles.begin(); p != particles.end(); p++) {

		list<Positionable<Particle> *>
				closestElements = octree->getIntersectionElements(
						(*p)->getCollisionShape().get());

		list<Positionable<Particle> *>::iterator closeP;
		for (closeP = closestElements.begin(); closeP != closestElements.end(); closeP++) {

			Particle * other = (*closeP)->getThis();
			if (other != (*p) && !(*p)->hasCollided(other)
					&& !other->hasCollided(*p)) {
				IntersectionData data = (*p)->checkCollision(*other);
				if (data.hasIntersected()) {
					printf("COLLISIONNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN   %d\n",
							RK4::getStep());
					(*p)->resolveCollision(*other, data);
					(*p)->addCollided(other);
					other->addCollided(*p);
				}
			}
		}
	}
}

// HUGE TODO!!!
bool ParticleGroup::resolveCollision(Collisionable& other,
		IntersectionData& data) {

	list<Particle *>::iterator p;
	for (p = particles.begin(); p != particles.end(); p++)
		(*p)->resetCollided();

	if (other.getCollisionableType() == C_ParticleGroup) {

		ParticleGroup& otherGroup = (ParticleGroup&) other;

		// First, get elements inside intersection of groups only

		// Elements inside this group that intersect with other
		list<Positionable<Particle> *> intersectionParticles =
				octree->getIntersectionElements(
						otherGroup.getCollisionShape().get());

		// Check collision for each particle of this group that falls in intersection
		list<Positionable<Particle> *>::iterator p;
		for (p = intersectionParticles.begin(); p
				!= intersectionParticles.end(); p++) {

			Particle * particle = (*p)->getThis();

			// Closest elements of other group
			list<Positionable<Particle> *> closestElements =
					otherGroup.octree->getIntersectionElements(
							particle->getCollisionShape().get());

			// And check collisions
			list<Positionable<Particle> *>::iterator closeP;
			for (closeP = closestElements.begin(); closeP
					!= closestElements.end(); closeP++) {

				Particle * otherParticle = (*closeP)->getThis();

				if (otherParticle != particle) {
					IntersectionData data = particle->checkCollision(
							*otherParticle);
					if (data.hasIntersected()) {
						particle->resolveCollision(*otherParticle, data);
						particle->addCollided(otherParticle);
						otherParticle->addCollided(particle);
					} else {
						//	speculateContact(particle, otherParticle, data);
					}
				}
			}
		}
	}

	return false;
}

ShapePtr ParticleGroup::getCollisionShape() {
	return boundingShape;
}

// PARA TESTEAR!!!
void ParticleGroup::render() {

	octree->render(NULL, true);
	/*
	 glColor4f(0, 1, 1.0, .05);
	 glTranslatef(centerOfMass.getX(), centerOfMass.getY(), centerOfMass.getZ());
	 glutWireCube(10);
	 glutWireSphere(boundingShape->getRadius(), 25, 25);
	 glTranslatef(-centerOfMass.getX(), -centerOfMass.getY(),
	 -centerOfMass.getZ());
	 */
	// Draw Particles
	list<Particle *>::iterator i;

	glColor3f(1.0, 1.0, 1.0);
	for (i = particles.begin(); i != particles.end(); i++) {
		Vector3 kPos = (*i)->getData().getPosition();

		//printf("%g,%g,%g\n", kPos.getX(), kPos.getY(), kPos.getZ());
		//printf("%g,%g,%g\n", vel.getX(), vel.getY(), vel.getZ());

		real m = fabs((*i)->getData().getMass());

		glTranslatef(kPos.getX(), kPos.getY(), kPos.getZ());
		glutSolidSphere(m, 3 + sqrt(m), 3 + sqrt(m));
		glTranslatef(-kPos.getX(), -kPos.getY(), -kPos.getZ());
	}

	//printf("\n\n\n");
}
