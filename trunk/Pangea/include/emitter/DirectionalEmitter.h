/*
 * DirectionalEmitter.h
 *
 *  Created on: Dec 16, 2010
 *      Author: mmerchan
 */

#ifndef DIRECTIONALEMITTER_H_
#define DIRECTIONALEMITTER_H_

#include "Emitter.h"
#include <SDL/SDL.h>

class DirectionalEmitter: public Emitter {

	private:

		Vector3 position;
		Vector3 direction;
		real angle;

		real turbulence;

		// Prueba de emit..
		void emitFunction() {
			// Create and add particle
			particles->addParticle(1, position, direction * speed);
		}

	public:

		DirectionalEmitter(ParticleWorld * world, Vector3 pos, Vector3 dir,
				real angle, real turbulence, real speed, real ratePerSecond) :
			Emitter(world, speed, ratePerSecond) {

			this->position = pos;
			dir.normalize();
			this->direction = dir;
			this->angle = angle;
			this->turbulence = turbulence;

			this->particles = ParticleGroupPtr(new ParticleGroup(position, false));
			this->world->addParticleGroup(particles);
		}

};

#endif /* DIRECTIONALEMITTER_H_ */
