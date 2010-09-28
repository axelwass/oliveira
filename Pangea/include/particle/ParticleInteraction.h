/*
 * ParticleInteraction.h
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "Particle.h"
#include "ParticleData.h"
#include "../force/Force.h"

#include <list>
using namespace std;

#ifndef PARTICLEINTERACTION_H_
#define PARTICLEINTERACTION_H_

class ParticleInteraction {

	private:
		Particle * particle;
		Particle * other;
		bool active;
		Force * force;

	public:
		ParticleInteraction(Particle * particle, Particle * other,
				Force * force);

		ParticleData getParticleData() {
			return particle->getData();
		}

		ParticleData getOtherParticleData() {
			return other->getData();
		}

		void resolve();

		void enable();
		void disable();
};

#endif /* PARTICLEINTERACTION_H_ */
