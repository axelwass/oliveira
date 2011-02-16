/*
 * ParticleWorld.h
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#include "../particle/Particle.h"
#include "../particle/ParticleGroup.h"
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
typedef tr1::shared_ptr<Octree<ParticleGroup> > OctreePtr;

class ParticleWorld {
	protected:

		list<Emitter *> emitters;

		list<ParticleGroupPtr> groups;
		OctreePtr groupsOctree;

		real precision;
		real time;

		Particle worldParticle;

		int particlesPerThread;

		void resolveGroupCollisions();

	public:

		ParticleWorld(real precision = 0.5);

		void addParticleGroup(ParticleGroupPtr group);

		void removeParticleGroup(ParticleGroupPtr group);

		void particleEmission();

		void addField(Force * field);

		void addEmitter(Emitter * emitter);

		void runPhysics();

		void updateForces();

		real getTime();

		void integrate();

		// PARA TESTEAR NOMAS
		void render();
};

#endif /* PARTICLEWORLD_H_ */
