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
#include "../force/SpringForce.h"
#include "../precision.h"
#include <list>
#include <vector>
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

		int particlesPerThread;


		/*
		 * Returns the last particle, at position v2
		 */
		Particle * addInternalSpring(const Vector3& v1, const Vector3& v2, real inverseMass,
				real k, real l);

	public:
		ParticleWorld(real precision = 0.5);

		void addParticle(real inverseMass = 1.0,
				const Vector3& pos = Vector3(), const Vector3& velocity =
						Vector3());

		void addWorldInteraction(Force * force);

		void addPerParticleInteraction(InterParticleForce * force);

		void addSpring(const Vector3& v1, const Vector3& v2, real inverseMass,
				real k, real l);

		void addSpringCircle(const Vector3& origin, real r, real inverseMass, real k,
				real l);

		void runPhysics();

		void updateForces();

		void integrate();

		void integrateNParticlesThread(void * lowerBound);

		void resolveCollisions();

		// PARA TESTEAR NOMAS
		void render();
};

#endif /* PARTICLEWORLD_H_ */
