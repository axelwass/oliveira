/*
 * Integrator.h
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#include "../particle/ParticleData.h"
#include "../force/Force.h"

#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

class Integrator {
public:

	/*
	 * The return value indicates if the integration is finished.
	 */
	virtual bool
	evaluate(Force * force, ParticleData * state, real t, real h) = 0;
	virtual void integrate(ParticleData * state, real h) = 0;

	virtual real getSlopeStep(real h) = 0;
	virtual ParticleData * getInitialData()= 0;
	virtual DerivativeData * getIntegrationSlope(real h)=0;
};

#endif /* INTEGRATOR_H_ */
