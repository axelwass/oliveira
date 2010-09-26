/*
 * GravitationalForce.h
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#include "InterParticleForce.h"
#include <math.h>
#include <iostream>

#ifndef GRAVITATIONALFORCE_H_
#define GRAVITATIONALFORCE_H_

class GravitationalForce: public InterParticleForce {
	private:

		static real GRAVITATIONAL_CONSTANT;

		GravitationalForce( Particle * other) :
			InterParticleForce( other) {
		}

		// Evaluation function
		DerivativeData _evaluate(real t, ParticleData * data) {

			cout << "ME: (" << data->getPosition().getX() << "," << data->getPosition().getY() << ")" << endl;

			Vector3 dir = other->getData().getPosition() - data->getPosition();


			cout << "DIR: (" << dir.getX() << "," << dir.getY() << ")" << endl;

			real r = dir.magnitude();
			dir.normalize();

			cout << "r: " << r << endl;

			Vector3 acc = dir * (GRAVITATIONAL_CONSTANT * data->getMass() * other->getData().getMass() * (1.0 / pow(r,2)));
			acc = Vector3();

			return DerivativeData(acc);
		}

		Force * _clone() {
			return new GravitationalForce(this->other);
		}

	public:
		GravitationalForce(){}

		virtual ~GravitationalForce(){}

		InterParticleForce * getFunctionCopy() {
			return new GravitationalForce( this->other);
		}
};

real GravitationalForce::GRAVITATIONAL_CONSTANT = 6.67428 * pow(10, -11);

#endif /* GRAVITATIONALFORCE_H_ */
