/*
 * ParticleData.h
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "../../../Generic/Generic.h"
#include "DerivativeData.h"

#define INFINITE_MASS -1

#ifndef PARTICLEDATA_H_
#define PARTICLEDATA_H_

class ParticleData {

	private:

		Vector3 position;
		Vector3 velocity;

		real inverseMass;

	public:

		// Returns true if the particle has finite mass
		bool hasFiniteMass();

		// Returns the mass of the particle
		real getMass();

		// Returns the mass of the particle
		real getInverseMass();

		// Sets mass of particle
		void setInverseMass(real inverseMass);

		// Sets velocity of particle
		void setVelocity(const Vector3& velocity);

		// Sets position of particle
		void setPosition(const Vector3& position);

		// Returns the velocity of the particle
		Vector3 getVelocity();

		// Returns the position of the particle
		Vector3 getPosition();

		// Check if two particles are equal
		bool operator==(ParticleData& other);

		/** Returns a copy of this derivative scaled to the given value.*/
		ParticleData operator*(const real value) {
			ParticleData out;
			out.velocity = this->velocity * value;
			out.position = this->position * value;
			out.inverseMass = this->inverseMass;
			return out;
		}

		/** Returns the value of the given derivative added to this*/
		ParticleData operator+(const DerivativeData& derivative) {
			ParticleData out;
			out.velocity = this->velocity + derivative.dv;
			out.position = this->position + derivative.dx;
			out.inverseMass = this->inverseMass;
			return out;
		}

		/** Returns the value of the given derivative added to this*/
		ParticleData operator+(const ParticleData& other) {
			ParticleData out;
			out.velocity = this->velocity + other.velocity;
			out.position = this->position + other.position;
			out.inverseMass = this->inverseMass;
			return out;
		}

		/** Returns the value of the given derivative substracted from this */
		ParticleData operator-(const ParticleData& other) {
			ParticleData out;
			out.velocity = this->velocity - other.velocity;
			out.position = this->position - other.position;
			out.inverseMass = this->inverseMass;
			return out;
		}

		// Uninitialized particle data
		ParticleData() {
		}

		// Defines data for particle
		ParticleData(const Vector3& position, real inverseMass);
};

#endif /* PARTICLEDATA_H_ */
