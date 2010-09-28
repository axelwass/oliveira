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

bool RK4::integrate(Force * force, ParticleData * state, real t, real h) {
	switch (this->step) {
	case 1:
		this->k1 = evaluate(force, state, t, 0, new DerivativeData());
		//printf("Acceleration: t: %f \t (%.16f,%.16f,%.16f) \n", t, k1.dv.getX(),k1.dv.getY(),k1.dv.getZ() );
		break;
	case 2:
		k2 = evaluate(force, state, t, h * 0.5, &k1);
		break;
	case 3:
		k3 = evaluate(force, state, t, h * 0.5, &k2);
		break;
	case 4:
		k4 = evaluate(force, state, t, h, &k3);
		(*state) = (*state) + ((k1 + (k2 + k3) * 2.0 + k4) * (h / 6.0));
		break;
	default:
		break;
	}

	if (this->step < 4) {
		this->step++;
		return false;
	} else {
		this->step = 1;
		return true;
	}
}

/*
 * Basically performs Euler to predict next derivatives (used by RK4)
 */
DerivativeData RK4::evaluate(Force * force, ParticleData * initial, real t,
		real h, DerivativeData * derivative) {
	ParticleData data = (*initial) + ((*derivative) * h);

	DerivativeData out = force->evaluate(t + h, &data);
	out.dx = data.getVelocity();
	return out;
}
