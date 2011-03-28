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

	GravitationalForce(Particle * other);

	// Evaluation function
	DerivativeData _evaluate(real t, ParticleData * data);

	Force * _clone();

public:
	GravitationalForce();

	virtual ~GravitationalForce();

	InterParticleForce * getFunctionCopy();
};

#endif /* GRAVITATIONALFORCE_H_ */
