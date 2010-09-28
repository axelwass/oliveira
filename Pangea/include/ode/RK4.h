/*
 * RK4.h
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#include "Integrator.h"
#include "../particle/DerivativeData.h"

#ifndef RK4_H_
#define RK4_H_

class RK4 : public Integrator{

	private:

		int step;

		DerivativeData k1;
		DerivativeData k2;
		DerivativeData k3;
		DerivativeData k4;

		ParticleData initialStepData;

	public:
		RK4();
		virtual ~RK4();

		bool integrate(Force * force, ParticleData * state, real t, real h);


		void applyStep(ParticleData * state, real h);
};

#endif /* RK4_H_ */
