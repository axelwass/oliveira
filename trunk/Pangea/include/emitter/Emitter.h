/*
 * Emitter.h
 *
 *  Created on: Dec 16, 2010
 *      Author: mmerchan
 */

#include "../particle/Particle.h"
#include "../world/ParticleWorld.h"

#ifndef EMITTER_H_
#define EMITTER_H_

class Emitter {

	protected:
		ParticleWorld * world;
		list<Particle *> particles;
		real speed;
		real ratePerSecond;

	public:

		Emitter(ParticleWorld * world, real speed, real ratePerSecond) {
			this->world = world;
			this->speed = speed;
			this->ratePerSecond = ratePerSecond;
		}

		list<Particle *> getParticleGroup() {
			return particles;
		}

		virtual void emit() = 0;
};

#endif /* EMITTER_H_ */
