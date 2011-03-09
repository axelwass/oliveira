/*
 * ParticleBridge.h
 *
 *  Created on: Dec 15, 2010
 *      Author: mmerchan
 */

#include "../../Vector3.h"
#include "ParticleRope.h"
#include "../../world/ParticleWorld.h"
#include <list>

#ifndef PARTICLEBRIDGE_H_
#define PARTICLEBRIDGE_H_

class ParticleBridge {

		Vector3 from, to;
		real height, density, k;

		ParticleRope * upperBridge;
		ParticleRope * lowerBridge;
		list<list<Particle *> > bridge;

		ParticleWorld * world;

		void initialize();

	public:
		ParticleBridge(ParticleWorld * world, Vector3 from, Vector3 to,
				real height, real density, real k);

		list<list<Particle *> > getBridge() {
			return bridge;
		}
};

#endif /* PARTICLEBRIDGE_H_ */

