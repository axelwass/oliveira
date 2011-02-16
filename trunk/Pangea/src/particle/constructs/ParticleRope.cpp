/*
 * ParticleRope.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: mmerchan
 */

#include "../../../include/force/ConstantForce.h"
#include "../../../include/particle/constructs/ParticleRope.h"

void ParticleRope::initialize() {

	if (!qty)
		return;

	rope = ParticleGroupPtr(new ParticleGroup((from + to) * .5, false));

	world->addParticleGroup(rope);

	Vector3 length = (to - from) * (1.0 / qty);

	// Infinite mass for first particle
	Particle * anchor = rope->addParticle(0, from);

	Particle * next;
	Particle * last = anchor;

	for (int i = 1; i < qty; i++) {

		// If last particle, infinite mass
		next = rope->addParticle(i == qty - 1 ? 0 : inverseMass, from + (length * i));

		if (i != 1)
			last->addForce(new SpringForce(k, length.magnitude(), next));

		next->addForce(new SpringForce(k, length.magnitude(), last));

		last->addForce(new ConstantForce(5, Vector3(0, -1, 0)));

		last = next;
	}

	last->addForce(new ConstantForce(5, Vector3(0, -1, 0)));
}

ParticleRope::ParticleRope(ParticleWorld * world, Vector3 from, Vector3 to,
		int qty, real k, real inverseMass) {
	this->world = world;
	this->from = from;
	this->to = to;
	this->qty = qty;
	this->k = k;
	this->inverseMass = inverseMass;

	initialize();
}

ParticleGroupPtr ParticleRope::getRope() {
	return rope;
}
