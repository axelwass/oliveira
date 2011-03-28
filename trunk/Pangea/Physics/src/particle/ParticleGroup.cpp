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
bool ParticleGroup::integrateStep(real time, real step) {
	list<Particle *>::iterator itr;

	octree->update();

	if (selfCollisions)
		resolveInternalCollisions();

	for (itr = particles.begin(); itr != particles.end(); itr++)
		(*itr)->integrate(time, step);

	return true;
}

void ParticleGroup::applyStep(real step) {
	list<Particle *>::iterator itr;

	centerOfMass = Vector3();

	// Apply step
	for (itr = particles.begin(); itr != particles.end(); itr++) {
		(*itr)->applyStep(step);

		real inverseMass = (*itr)->getData().getInverseMass();

		// If particle is finite, calculate center of mass
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

void ParticleGroup::repositionCollided(Particle * p1, Particle * p2) {

	// quick fix, TODO later
	if (p2->getCollisionableType() == C_RigidBody || p1->getCollisionableType()
			== C_RigidBody)
		return;

	// from 1 to 2
	Vector3 dist = p1->getPosition() - p2->getPosition();

	real ma = p1->getData().getMass();
	real mb = p2->getData().getMass();

	real diff = fabs(dist.magnitude() - fabs(ma) - fabs(mb)) + EPSILON; // 5 is radius of particle for now

	real ca, cb;

	// coeffs to balance repositioning
	if (ma == INFINITE_MASS && mb == INFINITE_MASS)
		return;
	else if (ma == INFINITE_MASS) {
		ca = 1;
		cb = 0;
	} else if (mb == INFINITE_MASS) {
		ca = 0;
		cb = 1;
	} else {
		ca = ma / (ma + mb);
		cb = mb / (ma + mb);
	}

	dist.normalize();

	ParticleData d1 = p1->getData();
	d1.setPosition(d1.getPosition() + dist * diff * cb);
	p1->setData(d1);

	ParticleData d2 = p2->getData();
	d2.setPosition(d2.getPosition() - dist * diff * ca);
	p2->setData(d2);
}

void ParticleGroup::resolveInternalCollisions() {
	list<Particle *>::iterator p;
	for (p = particles.begin(); p != particles.end(); p++) {

		list<Positionable<Particle> *>
				closestElements = octree->getIntersectionElements(
						(*p)->getCollisionShape().get());

		list<Positionable<Particle> *>::iterator closeP;
		for (closeP = closestElements.begin(); closeP != closestElements.end(); closeP++) {

			Particle * other = (*closeP)->getThis();
			if (other != (*p)) {

				IntersectionData data = (*p)->checkCollision(*other);
				if (data.hasIntersected()) {
					repositionCollided(*p, other);
					(*p)->resolveCollision(*other, data);
				}
			}
		}
	}
}

bool ParticleGroup::resolveCollision(Collisionable& other,
		IntersectionData& data) {

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
						repositionCollided(particle, otherParticle);
						particle->resolveCollision(*otherParticle, data);
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

	//octree->render(NULL, true);
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

