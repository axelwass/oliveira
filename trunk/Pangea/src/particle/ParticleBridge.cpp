/*
 * ParticleBridge.cpp
 *
 *  Created on: Dec 15, 2010
 *      Author: mmerchan
 */

#include "../../include/particle/ParticleBridge.h"

ParticleBridge::ParticleBridge(ParticleWorld * world, Vector3 from, Vector3 to,
		real height, real density, real k) {
	this->world = world;
	this->from = from;
	this->to = to;
	this->height = height;
	this->k = k;
	this->density = density;

	this->initialize();
}

void ParticleBridge::initialize() {

	// Prepare upperBridge positions
	Vector3 uppFrom, uppTo;
	uppFrom = Vector3(from.getX(), from.getY() + height, from.getZ());
	uppTo = Vector3(to.getX(), to.getY() + height, to.getZ());

	// Get both ropes
	lowerBridge = new ParticleRope(world, from, to, density, k);
	upperBridge = new ParticleRope(world, uppFrom, uppTo, density, k);

	// Prepare particle list
	list<Particle *> upperParticles = upperBridge->getRope();
	list<Particle *> lowerParticles = lowerBridge->getRope();
	bridge.push_back(lowerParticles);
	bridge.push_back(upperParticles);

	// And connect both ropes
	list<Particle*>::iterator upper = upperParticles.begin();
	list<Particle*>::iterator lower = lowerParticles.begin();
	for (unsigned i = 0; i < upperParticles.size(); upper++, lower++, i++) {

		// Connect i-eth particle
		world->addParticleInteraction((*upper), (*lower), new SpringForce(k,
				height, (*lower)));
		world->addParticleInteraction((*lower), (*upper), new SpringForce(k,
				height, (*upper)));


		// Cross connect i-eth particle /
		if (i != upperParticles.size() - 1) {
			lower++;

			real distance = ((*lower)->getData().getPosition() - (*upper)->getData().getPosition()).magnitude();
			if (i != 0)
				world->addParticleInteraction((*upper), (*lower),
						new SpringForce(k, distance, (*lower)));

			if (i != upperParticles.size() - 2)
				world->addParticleInteraction((*lower), (*upper),
						new SpringForce(k, distance, (*upper)));
			lower--;
		}


		// Cross connect i-eth particle /
		if (i != upperParticles.size() - 1) {
			upper++;
			real distance = ((*lower)->getData().getPosition() - (*upper)->getData().getPosition()).magnitude();
			if (i != upperParticles.size() - 2)
				world->addParticleInteraction((*upper), (*lower),
						new SpringForce(k, distance, (*lower)));

			if (i != 0)
				world->addParticleInteraction((*lower), (*upper),
						new SpringForce(k, distance, (*upper)));
			upper--;
		}
	}
}

