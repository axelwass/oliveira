/*
 * Particle.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "../../include/particle/Particle.h"

// Construct particle in origin with mass 1
Particle::Particle() {
	this->data = ParticleData(Vector3(), 1);

	this->forceAccum = new NullForce();
	this->integrator = new RK4();
}

// Construct particle with given position and mass
Particle::Particle(const Vector3& position, real inverseMass) {
	this->data = ParticleData(position, inverseMass);

	this->forceAccum = new NullForce();
	this->integrator = new RK4();
}

// Construct particle with given data
Particle::Particle(const ParticleData& data) {
	this->data = data;

	this->forceAccum = new NullForce();
	this->integrator = new RK4();
}

// Get particle data
ParticleData Particle::getData() {
	return data;
}

// Check if two particles are equal
bool Particle::operator==(Particle& other) {
	return data == other.data;
}

void Particle::addForce(Force * force) {
	if (force != NULL) {
		*(this->forceAccum) += force;
	}
}

void Particle::clearForces() {
	delete this->forceAccum;
	this->forceAccum = new NullForce();
}

bool Particle::integrate(real t, real h) {
	bool out = integrator->integrate(this->forceAccum, &this->data, t, h);
	return out;
}

void Particle::applyStep(real h) {
	integrator->applyStep(&this->data, h);
}
