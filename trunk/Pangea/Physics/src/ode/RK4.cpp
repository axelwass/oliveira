/*
 * RK4.cpp
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#include "../../include/ode/RK4.h"
#include <iostream>
using namespace std;

RK4::RK4() {
	this->step = 1;
}

RK4::~RK4() {
}

void RK4::applyStep(ParticleData * state, real h) {
	switch (this->step) {
	case 1:
		(*state) = initialStepData + (k1 * (h * .5));
		this->step++;
		break;
	case 2:
		(*state) = initialStepData + (k2 * (h * .5));
		this->step++;
		break;
	case 3:
		(*state) = initialStepData + (k3 * h);
		this->step++;
		break;
	case 4:
		(*state) = initialStepData + ((k1 + (k2 + k3) * 2.0 + k4) * (h / 6.0));
		this->step = 1;
		break;
	default:
		break;
	}
}

bool RK4::integrate(Force * force, ParticleData * state, real t, real h) {

	ParticleData tmp;

	switch (this->step) {
	case 1:
		initialStepData = (*state);
		k1 = force->evaluate(t, &initialStepData);
		k1.dx = initialStepData.getVelocity();
		break;
	case 2:
		tmp = initialStepData + k1 * (h / 2.0);
		k2 = force->evaluate(t + h / 2.0, &tmp);
		k2.dx = tmp.getVelocity();
		break;
	case 3:
		tmp = initialStepData + k2 * (h / 2.0);
		k3 = force->evaluate(t + h / 2.0, &tmp);
		k3.dx = tmp.getVelocity();
		break;
	case 4:
		tmp = initialStepData + k3 * h;
		k4 = force->evaluate(t + h, &tmp);
		k4.dx = tmp.getVelocity();
		break;
	default:
		break;
	}

	if (this->step < 4) {
		return false;
	} else {
		return true;
	}
}
