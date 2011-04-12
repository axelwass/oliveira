/*
 * particle.h
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include <stdio.h>
#include <list>
#include "../../../Generic/Generic.h"
#include "../Positionable.h"
#include "ParticleData.h"
#include "../ode/RK4.h"
#include "../force/Force.h"
#include "../force/NullForce.h"
#include "Collisionable.h"

#ifndef PARTICLE_H_
#define PARTICLE_H_

class Particle: public Positionable<Particle> , public Collisionable {

protected:

	// Information about particle
	ParticleData data;

	// Particle private integrator
	Integrator * integrator;

	// Particle force accumulator
	Force * forceAccum;

	list<Particle *> collided;

public:

	void addCollided(Particle * p) {
		collided.push_back(p);
	}

	bool hasCollided(Particle * p) {
		list<Particle *>::iterator c;
		for (c = collided.begin(); c != collided.end(); c++)
			if ((*c) == p)
				return true;

		return false;
	}

	void resetCollided() {
		collided.clear();
	}

	Particle * getThis() {
		return this;
	}

	// From positionable
	Vector3 getPosition() {
		return data.getPosition();
	}

	virtual CollisionableType getCollisionableType() {
		return C_Particle;
	}

	// Construct particle in origin with mass 1
	Particle();

	// Construct particle with given position and mass
	Particle(const Vector3& position, real inverseMass);

	// Construct particle with given data
	Particle(const ParticleData& data);

	// Get particle data
	ParticleData getData();

	// Change particle data
	void setData(const ParticleData& data);

	// Check if two particles are equal
	bool operator==(Particle& other);

	Integrator * getIntegrator() {
		return integrator;
	}

	void evaluate(real t, real h);

	void integrate(real h);

	virtual void addForce(Force * force);

	void clearForces();

	virtual bool resolveCollision(Collisionable& other, IntersectionData& data);

	virtual ShapePtr getCollisionShape();

};

#endif /* PARTICLE_H_ */
