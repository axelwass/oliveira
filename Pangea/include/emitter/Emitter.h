/*
 * Emitter.h
 *
 *  Created on: Dec 16, 2010
 *      Author: mmerchan
 */

#include "../particle/Particle.h"
#include "../particle/ParticleGroup.h"
#include "../world/ParticleWorld.h"

#include <SDL/SDL.h>

#ifndef EMITTER_H_
#define EMITTER_H_

class Emitter {

	protected:
		ParticleWorld * world;
		ParticleGroupPtr particles;
		real speed;
		real ratePerSecond;
		real timeCounter;

		virtual void emitFunction() = 0;

	public:

		Emitter(ParticleWorld * world, real speed, real ratePerSecond) {
			this->world = world;
			this->speed = speed;
			this->ratePerSecond = ratePerSecond;
			this->timeCounter = 0;
		}

		ParticleGroupPtr getParticleGroup() {
			return particles;
		}

		void emit() {

			real timePassed = world->getTime() - timeCounter;

			//cout << world->getTime() << "," << SDL_GetTicks() << endl;

			// longer than 2 secs for now
			if (timePassed > 1.0 / ratePerSecond) {
				timeCounter = world->getTime();
				emitFunction();
			}

		}
};

#endif /* EMITTER_H_ */
