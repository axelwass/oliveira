/*
 * ParticleRope.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: mmerchan
 */

#include "../../include/force/ConstantForce.h"
#include "../../include/particle/ParticleRope.h"

void ParticleRope::initialize() {

	rope = ParticleGroupPtr(new ParticleGroup((from + to) * .5, false));

	world->addParticleGroup(rope);

	 real qty = (to - from).magnitude() * density;

	 Vector3 length = (to - from) * (1 / qty);

	 Particle * anchor = rope->addParticle(1, from);

	 Particle * next;
	 Particle * last = anchor;

	 for (int i = 1; i < qty; i++) {
	 next = rope->addParticle(1, from + (length * i));

	 if (i != 1)
	 last->addForce(new SpringForce(k, length.magnitude(), next));

	 if (i != qty - 1) {
	 next->addForce(new SpringForce(k, length.magnitude(), last));

	 next->addForce(new ConstantForce(5, Vector3(0, -1, 0)));
	 }
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

ParticleGroupPtr ParticleRope::getRope() {
	return rope;
}
