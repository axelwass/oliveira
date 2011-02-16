/*
 * ParticleRope.h
 *
 *  Created on: Dec 14, 2010
 *      Author: mmerchan
 */

#include "../../Vector3.h"
#include "../Particle.h"

#include "../ParticleGroup.h"
#include "../../world/ParticleWorld.h"
#include <list>
#include <tr1/memory>

#ifndef PARTICLEROPE_H_
#define PARTICLEROPE_H_

class ParticleRope;

typedef tr1::shared_ptr<ParticleRope> ParticleRopePtr;

class ParticleRope {

	private:
		Vector3 from, to;
		int qty;
		real k;
		real inverseMass;
		ParticleGroupPtr rope;
		ParticleWorld * world;

		void initialize();

	public:

		ParticleRope(ParticleWorld * world, Vector3 from, Vector3 to, int qty,
				real k, real inverseMass);

		ParticleGroupPtr getRope();
};

#endif /* PARTICLEROPE_H_ */

