/*
 * ParticleRope.h
 *
 *  Created on: Dec 14, 2010
 *      Author: mmerchan
 */

#include "../Vector3.h"
#include "Particle.h"

#include "ParticleGroup.h"
#include "../world/ParticleWorld.h"
#include <list>

#ifndef PARTICLEROPE_H_
#define PARTICLEROPE_H_

class ParticleRope {

	private:
		Vector3 from, to;
		real density;
		real k;
		ParticleGroupPtr rope;
		ParticleWorld * world;

		void initialize();

	public:

		ParticleRope(ParticleWorld * world, Vector3 from, Vector3 to,
				real density, real k);

		ParticleGroupPtr getRope();
};

#endif /* PARTICLEROPE_H_ */

