/*
 * InterParticleForce.h
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#include "../particle/Particle.h"

#ifndef INTERPARTICLEFORCE_H_
#define INTERPARTICLEFORCE_H_

/**
 * The idea of this class is to provide a general interface for interacting particles.
 * With this in mind, one can create a class and use the world to assign every interaction possible
 * in an easy way.
 */
class InterParticleForce : public Force {
	protected:
		Particle * other;

		InterParticleForce(Particle * other){
			this->other = other;
		}

	public:
		InterParticleForce(){
			this->other = NULL;
		}

		virtual ~InterParticleForce(){

		}

		void setParticleData(Particle * other){
			this->other = other;
		}
		virtual InterParticleForce * getFunctionCopy() = 0;
};

#endif /* INTERPARTICLEFORCE_H_ */
