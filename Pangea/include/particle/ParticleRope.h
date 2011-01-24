/*
 * ParticleRope.h
 *
 *  Created on: Dec 14, 2010
 *      Author: mmerchan
 */

#include "../Vector3.h"
#include "Particle.h"
#include "../world/ParticleWorld.h"
#include <list>

#ifndef PARTICLEROPE_H_
#define PARTICLEROPE_H_

class ParticleRope {

	private:
		Vector3 from, to;
		real density;
		real k;
		list<Particle *> rope;
		ParticleWorld * world;

		void initialize();

	public:

		ParticleRope(ParticleWorld * world, Vector3 from, Vector3 to, real density, real k);

		list<Particle *> getRope();
};

#endif /* PARTICLEROPE_H_ */

