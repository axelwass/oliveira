/*
 * ConstantForce.h
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "Force.h"
#include <iostream>
using namespace std;

#ifndef CONSTANTFORCE_H_
#define CONSTANTFORCE_H_

class ConstantForce: public Force {
	private:
		Vector3 force;

		// Evaluation function
		DerivativeData _evaluate(real t, ParticleData * data) {
			if (data->getInverseMass())
				return DerivativeData(this->force * data->getInverseMass());
			else
				return DerivativeData();
		}

		Force * _clone() {
			return new ConstantForce(this->force.magnitude(), this->force);
		}

	public:
		ConstantForce(real c, const Vector3& force) :
			Force() {
			this->force = force;
			this->force.normalize();
			this->force *= c;
		}

		virtual ~ConstantForce() {
		}
};

#endif /* CONSTANTFORCE_H_ */
