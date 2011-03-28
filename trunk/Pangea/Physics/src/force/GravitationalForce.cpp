/*
 * GravitationalForce.cpp
 *
 *  Created on: Mar 26, 2011
 *      Author: mariano
 */

#include "../../include/force/GravitationalForce.h"

real GravitationalForce::GRAVITATIONAL_CONSTANT = 6.67428 * pow(10, 1); // 10e-11 is real


GravitationalForce::GravitationalForce(Particle * other) :
	InterParticleForce(other) {
}

// Evaluation function
DerivativeData GravitationalForce::_evaluate(real t, ParticleData * data) {

	Vector3 dir = other->getData().getPosition() - data->getPosition();

	real r = dir.magnitude();
	dir.normalize();

	Vector3 acc = dir * (GRAVITATIONAL_CONSTANT * other->getData().getMass()
			* (1.0 / pow(r, 2)));

	return DerivativeData(acc);
}

Force * GravitationalForce::_clone() {
	return new GravitationalForce(this->other);
}

GravitationalForce::GravitationalForce() {
}

GravitationalForce::~GravitationalForce() {
}

InterParticleForce * GravitationalForce::getFunctionCopy() {
	return new GravitationalForce(this->other);
}
