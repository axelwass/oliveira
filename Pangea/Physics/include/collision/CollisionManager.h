/*
 * CollisionManager.h
 *
 *  Created on: Apr 14, 2011
 *      Author: mmerchan
 */

#include "../particle/Particle.h"
#include "../particle/ParticleGroup.h"
#include "CollisionEvent.h"

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

class CollisionManager {

protected:

	// Useful for all particle related
	typedef tr1::shared_ptr<Octree<Particle> > OctreePtr;

	OctreePtr octree;
	list<Particle *> * particles;

	list<CollisionEventPtr> collided;
private:

	void add(CollisionEventPtr c);

	void speculateContact(Particle * p1, Particle * p2, real h);

	void resolve();

public:

	CollisionManager(ParticleGroup * group) {
		this->octree = group->getOctree();
		this->particles = group->getParticles();
	}

	void speculate(real h);
};

#endif /* COLLISIONMANAGER_H_ */
