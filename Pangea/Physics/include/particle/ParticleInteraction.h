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

		bool isDual(){
			return other!=NULL;
		}

		ParticleData getParticleData() {
			return particle->getData();
		}

		ParticleData getOtherParticleData() {
			return other!= NULL? other->getData() : ParticleData();
		}

		void resolve();

		void enable();
		void disable();
};

#endif /* PARTICLEINTERACTION_H_ */
