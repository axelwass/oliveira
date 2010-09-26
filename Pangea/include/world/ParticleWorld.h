/*
 * ParticleWorld.h
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#include "../particle/Particle.h"
#include "../particle/ParticleInteraction.h"
#include "../force/InterParticleForce.h"
#include "../Vector3.h"
#include "../precision.h"
#include <list>
using namespace std;

#ifndef PARTICLEWORLD_H_
#define PARTICLEWORLD_H_

class ParticleWorld {
	private:
		list<Particle*> particles;
		list<ParticleInteraction *> interactions;

		real precision;
		real time;

		Particle worldParticle;

	public:
		ParticleWorld(real precision = 0.5);

		void addParticle(real inverseMass = 1.0, const Vector3& pos = Vector3(), const Vector3& velocity = Vector3());

		void addWorldInteraction(Force * force);

		void addPerParticleInteraction(InterParticleForce * force);

		void runPhysics();

		void updateForces();

		void integrate();

		void resolveCollisions();

		// PARA TESTEAR NOMAS
		void render();
};

#endif /* PARTICLEWORLD_H_ */
