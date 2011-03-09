/*
 * ParticleData.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "../../include/particle/ParticleData.h"

// Returns true if the particle has finite mass
bool ParticleData::hasFiniteMass() {
	return inverseMass != 0;
}

// Returns the mass of the particle
real ParticleData::getMass() {
	return hasFiniteMass() ? 1.0 / inverseMass : INFINITE_MASS;
}

// Returns the mass of the particle
real ParticleData::getInverseMass() {
	return inverseMass;
}

// Sets mass of particle
void ParticleData::setInverseMass(real inverseMass) {
	this->inverseMass = (inverseMass != 0) ? inverseMass : -1.0;

}

// Sets velocity of particle
void ParticleData::setVelocity(const Vector3& velocity) {
	this->velocity = velocity;
}

// Sets position of particle
void ParticleData::setPosition(const Vector3& position) {
	this->position = position;
}

// Returns the velocity of the particle
Vector3 ParticleData::getVelocity() {
	return velocity;
}

// Returns the position of the particle
Vector3 ParticleData::getPosition() {
	return position;
}

// Check if two particleData are equal
bool ParticleData::operator==(ParticleData& other) {
	return (position == other.position) && (velocity == other.velocity)
			&& (inverseMass == other.inverseMass);
}

// Creates a particle with a defined position and mass
ParticleData::ParticleData(const Vector3& position, real inverseMass) {
	this->position = position;
	this->velocity = Vector3();
	this->inverseMass = inverseMass;
}
