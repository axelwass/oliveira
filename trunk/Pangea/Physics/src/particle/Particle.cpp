/*
 * Particle.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "../../include/particle/Particle.h"
#include "../../include/shape/Sphere.h"

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
	//this->path.push_back(this->data.getPosition());
	bool out = integrator->integrate(this->forceAccum, &this->data, t, h);
	return out;
}

void Particle::setData(const ParticleData& data) {
	this->data = data;
}

void Particle::applyStep(real h) {
	integrator->applyStep(&this->data, h);
}

ShapePtr Particle::getCollisionShape() {
	// Assume radius for now..
	ShapePtr out(new Sphere(fabs(data.getMass())));
	out->setPosition(this->data.getPosition());
	return out;
}

// Must resolve BOTH particles!
bool Particle::resolveCollision(Collisionable& other,
		IntersectionData& intersectionData) {

	Vector3 impulseNormal = intersectionData.getNormal();

	if (other.getCollisionableType() == C_Particle
			|| other.getCollisionableType() == C_RigidBody) {

		Particle& p = (Particle&) other;

		real ma = data.getMass();
		real mb = p.data.getMass();

		// Perfectly elastic
		real coeff;
		if (ma == INFINITE_MASS && mb == INFINITE_MASS)
			return true;
		else if (ma == INFINITE_MASS)
			coeff = mb;
		else if (mb == INFINITE_MASS)
			coeff = ma;
		else
			coeff = (ma * mb) / (ma + mb);

		Vector3 va = data.getVelocity();
		Vector3 vb = p.data.getVelocity();

		Vector3 impulse = impulseNormal * (2 * coeff * ((va - vb)
				* impulseNormal));

		Vector3 finalVela = impulse * -1 * this->data.getInverseMass();
		Vector3 finalVelb = impulse * p.data.getInverseMass();

		this->data.setVelocity(va + finalVela);
		p.data.setVelocity(vb + finalVelb);

		return true;
	}

	// Estaria bueno armar un collisionListener aca para avisar que colisiono, avisar ambas particulas

	return false;
}
