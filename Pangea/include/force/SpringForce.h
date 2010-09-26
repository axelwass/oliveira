/*
 * SpringForce.h
 *
 *  Created on: 26/09/2010
 *      Author: Mariano
 */

#include "InterParticleForce.h"
#include <math.h>
#include <iostream>

#ifndef SPRINGFORCE_H_
#define SPRINGFORCE_H_

class SpringForce: public InterParticleForce {
	private:

		real k, length;

		SpringForce(Particle * other) :
			InterParticleForce(other) {
		}

		// Evaluation function
		DerivativeData _evaluate(real t, ParticleData * data) {

			// Calculate the direction of the spring
			Vector3 acc = data->getPosition() - other->getData().getPosition();

			// Calculate the magnitude of the force
			real magnitude = acc.magnitude(); // this is the distance between particles
			magnitude = magnitude - this->length;
			magnitude *= this->k;

			// Calculate the final force and apply it
			acc.normalize();
			acc *= -magnitude;

			acc *= data->getInverseMass();

			return DerivativeData(acc);
		}

		Force * _clone() {
			SpringForce * out = new SpringForce(this->other);
			out->k = this->k;
			out->length = this->length;
			return out;
		}

	public:
		SpringForce(real k, real length, Particle * other) {
			this->k = k;
			this->length = length;
			this->other = other;
		}

		virtual ~SpringForce() {
		}

		InterParticleForce * getFunctionCopy() {
			SpringForce * out = new SpringForce(this->other);
			out->k = this->k;
			out->length = this->length;
			return out;
		}
};

#endif /* SPRINGFORCE_H_ */
