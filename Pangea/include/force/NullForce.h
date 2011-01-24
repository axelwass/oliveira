/*
 * NullForce.h
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#ifndef NULLFORCE_H_
#define NULLFORCE_H_

class NullForce: public Force {

		// Evaluation function
		DerivativeData _evaluate(real t, ParticleData * data) {
			return DerivativeData();
		}

		Force * _clone(){
			return new NullForce();
		}

	public:

		NullForce() {
		}
		virtual ~NullForce() {
		}
};

#endif /* NULLFORCE_H_ */
