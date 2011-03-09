/*
 * ParticlePlane.cpp
 *
 *  Created on: Feb 16, 2011
 *      Author: mmerchan
 */

#include "../../../include/particle/constructs/ParticlePlane.h"
#include "../../../include/particle/constructs/ParticleRope.h"

ParticlePlane::ParticlePlane(ParticleWorld * world, Vector3 position, real l,
		real w, int subdivLength, int subdivWidth, real k) {
	this->world = world;
	this->position = position;
	this->width = w;
	this->length = l;
	this->subdivLength = subdivLength;
	this->subdivWidth = subdivWidth;
	this->k = k;

	this->plane = ParticleGroupPtr(new ParticleGroup(position, false));

	initialize();
}

void ParticlePlane::initialize() {
	Vector3 from = position + Vector3(length / 2.0, 0, -width / 2.0);
	Vector3 to = position + Vector3(-length / 2.0, 0, -width / 2.0);
	Vector3 translation(0, 0, width / subdivWidth);

	ParticleRopePtr prev = ParticleRopePtr(new ParticleRope(world, from, to,
			subdivLength, k, 0));
	ParticleRopePtr next = prev;

	list<Particle *> prevList = prev->getRope()->getParticles();
	list<Particle *> nextList;

	for (int i = 1; i < subdivWidth; i++) {

		next = ParticleRopePtr(new ParticleRope(world, from + translation * i,
				to + translation * i, subdivLength, k, i == subdivWidth - 1 ? 0
						: .25));
		nextList = next->getRope()->getParticles();

		list<Particle *>::iterator nextItr = nextList.begin();
		list<Particle *>::iterator prevItr = prevList.begin();

		for (; nextItr != nextList.end() || prevItr != prevList.end(); nextItr++, prevItr++) {

			real distance = translation.getZ();

			(*nextItr)->addForce(new SpringForce(k, distance, *prevItr));
			(*prevItr)->addForce(new SpringForce(k, distance, *nextItr));

			// Add just this row, next row will be handled in next iteration
			this->plane->addParticle(*prevItr);

			if (i == subdivWidth - 1)
				this->plane->addParticle(*nextItr);
		}

		// Remove element from world so it destructs
		world->removeParticleGroup(prev->getRope());
		prev = next;
		prevList = nextList;
	}

	// Remove last one
	world->removeParticleGroup(prev->getRope());

	world->addParticleGroup(plane);
}
