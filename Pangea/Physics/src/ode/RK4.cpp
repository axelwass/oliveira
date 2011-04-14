/*
 * RK4.cpp
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#include "../../include/ode/RK4.h"
#include <stdio.h>
#include <iostream>
using namespace std;

int RK4::globalStep = 1;
int RK4::maxSteps = 4;

RK4::RK4() {

}

RK4::~RK4() {
}

real RK4::getSlopeStep(real h) {
	return h / 6.0;
}

ParticleData * RK4::getInitialData() {
	return &initialStepData;
}

DerivativeData * RK4::getIntegrationSlope(real h) {
	return &slope;
}

void RK4::integrate(ParticleData * state, real h) {
	switch (globalStep) {
	case 1:
		(*state) = initialStepData + (k1 * (h * .5));
		break;
	case 2:
		(*state) = initialStepData + (k2 * (h * .5));
		break;
	case 3:
		(*state) = initialStepData + (k3 * h);
		break;
	case 4:
		(*state) = initialStepData + (slope * (h / 6.0));

	//	printf("Initial state pos.Y: %g\n", initialStepData.getPosition().getY());
	//	printf("Final state pos.Y: %g\n", state->getPosition().getY());
	//	printf("Final slope vel.Y: %g\n", (slope * (h / 6.0)).dx.getY());

		break;
	default:
		break;
	}
}

bool RK4::evaluate(Force * force, ParticleData * state, real t, real h) {

	ParticleData tmp;

	switch (globalStep) {
	case 1:
		initialStepData = (*state);
		k1 = force->evaluate(t, &initialStepData);
		k1.dx = initialStepData.getVelocity();
		return false;
	case 2:
		tmp = initialStepData + k1 * (h / 2.0);
		k2 = force->evaluate(t + h / 2.0, &tmp);
		k2.dx = tmp.getVelocity();
		return false;
	case 3:
		tmp = initialStepData + k2 * (h / 2.0);
		k3 = force->evaluate(t + h / 2.0, &tmp);
		k3.dx = tmp.getVelocity();
		return false;
	case 4:
		tmp = initialStepData + k3 * h;
		k4 = force->evaluate(t + h, &tmp);
		k4.dx = tmp.getVelocity();
		slope = k1 + (k2 + k3) * 2.0 + k4;
		return true;
	default:
		return false;
	}

}
