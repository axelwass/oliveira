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
#include "../octree/Octree.h"
#include <list>
#include <vector>
using namespace std;

class Emitter;

#ifndef PARTICLEWORLD_H_
#define PARTICLEWORLD_H_


// Useful for all particle related
typedef tr1::shared_ptr<Octree<Particle> > OctreePtr;

class ParticleWorld {
	protected:

		// For now, just one octree, no groups yet (todo: groups)
		OctreePtr particleOctree;

		list<Particle*> particles;
		list<Emitter *> emitters;
		list<ParticleInteraction *> interactions;
		list<Force *> fields;

		real precision;
		real time;

		Particle worldParticle;

		int particlesPerThread;

		/*
		 * Returns the last particle, at position v2
		 */
		Particle * addInternalSpring(const Vector3& v1, const Vector3& v2,
				real inverseMass, real k, real l);

	public:
		ParticleWorld(real precision = 0.5);

		void printParticles() {
			printf("Quantity: %d\n", this->particles.size());
			printf("Interaction: %d\n", this->interactions.size());
		}

		Particle * addParticle(real inverseMass = 1.0, const Vector3& pos =
				Vector3(), const Vector3& velocity = Vector3());

		void particleEmission();

		void addField(Force * field);

		void addEmitter(Emitter * emitter);

		void addWorldInteraction(Force * force);

		void addPerParticleInteraction(InterParticleForce * force);

		void addParticleInteraction(Particle * p1, Particle * p2, Force * f);

		void addSpring(const Vector3& v1, const Vector3& v2, real inverseMass,
				real k, real l);

		void addSpringCircle(const Vector3& origin, real r, real inverseMass,
				real k, int qty);

		void runPhysics();

		void updateForces();

		real getTime();

		void integrate();

		void integrateNParticlesThread(void * lowerBound);

		void resolveCollisions();

		void repositionCollided(Particle * p1, Particle * p2);

		// PARA TESTEAR NOMAS
		void render();
};

#endif /* PARTICLEWORLD_H_ */
