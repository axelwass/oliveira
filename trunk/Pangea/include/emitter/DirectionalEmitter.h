/*
 * DirectionalEmitter.h
 *
 *  Created on: Dec 16, 2010
 *      Author: mmerchan
 */

#ifndef DIRECTIONALEMITTER_H_
#define DIRECTIONALEMITTER_H_

#include "Emitter.h"

class DirectionalEmitter: public Emitter {

	private:

		Vector3 position;
		Vector3 direction;
		real angle;

		real time;

		int turbulence;

	public:

		DirectionalEmitter(ParticleWorld * world, Vector3 pos, Vector3 dir,
				real angle, int turbulence, real speed, real ratePerSecond) :
			Emitter(world, speed, ratePerSecond) {
			this->position = pos;
			dir.normalize();
			this->direction = dir;
			this->angle = angle;
			this->time = world->getTime();
			this->turbulence = turbulence;
		}

		// Prueba de emit..
		void emit() {

			real timePassed = world->getTime() - time;

			if (timePassed > 2) {

				time = world->getTime();
				real step = angle / 10.0;

				for (real i = -angle; i < angle; i += step) {

					Vector3 sparse = Vector3(direction);
					sparse += Vector3(cos(i), sin(i), 0);
					sparse.normalize();

					// Create and add particle
					Particle * p = world->addParticle(1, position, sparse
							* speed);
					particles.push_back(p);
				}
			}
		}
};

#endif /* DIRECTIONALEMITTER_H_ */
