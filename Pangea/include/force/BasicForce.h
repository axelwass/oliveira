/*
 * BasicForce.h
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "Force.h"

#ifndef BASICFORCE_H_
#define BASICFORCE_H_

class BasicForce : public Force {
	private:
		Vector3 force;

	public:
		// Evaluation function
		virtual ParticleData evaluate(real t, ParticleData * from, ParticleData * other) {
			return ParticleData( Vector3(), from->getInverseMass());
		}

		BasicForce(int c, const Vector3& force) : Force(){
			this->force = force;
			this->force.normalize();
			this->force *= c;
		}

		virtual ~ConstantForce(){}
};



#endif /* BASICFORCE_H_ */
