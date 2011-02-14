/*
 * ParticleRope.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: mmerchan
 */

#include "../../include/force/ConstantForce.h"
#include "../../include/particle/ParticleRope.h"

void ParticleRope::initialize() {
	real qty = (to - from).magnitude() * density;

	Vector3 length = (to - from) * (1 / qty);

	Particle * anchor = world->addParticle(1, from);
	rope.push_back(anchor);

	Particle * next;
	Particle * last = anchor;

	for (int i = 1; i < qty; i++) {
		next = world->addParticle(1, from + (length * i));

		if (i != 1)
			world->addParticleInteraction(last, next, new SpringForce(k,
					length.magnitude(), next));

		if (i != qty - 1) {
			world->addParticleInteraction(next, last, new SpringForce(k,
					length.magnitude(), last));

			world->addParticleInteraction(next, NULL, new ConstantForce(25,
					Vector3(0, -1, 0)));
		}

		rope.push_back(next);
		last = next;
	}

}

ParticleRope::ParticleRope(ParticleWorld * world, Vector3 from, Vector3 to,
		real density, real k) {
	this->world = world;
	this->from = from;
	this->to = to;
	this->density = density;
	this->k = k;

	initialize();
}

list<Particle *> ParticleRope::getRope() {
	return rope;
}
