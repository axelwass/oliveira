/*
 * ParticlePlane.h
 *
 *  Created on: Feb 16, 2011
 *      Author: mmerchan
 */

#include "../../../../Generic/Generic.h"
#include "../Particle.h"

#include "../ParticleGroup.h"
#include "../../world/ParticleWorld.h"
#include <list>
using namespace std;

#ifndef PARTICLEPLANE_H_
#define PARTICLEPLANE_H_

class ParticlePlane {

	private:
		Vector3 position;
		real length, width;
		int subdivLength, subdivWidth;
		real k;
		ParticleGroupPtr plane;
		ParticleWorld * world;

		void initialize();

	public:
		ParticlePlane(ParticleWorld * world, Vector3 position, real l, real w,
				int subdivLength, int subdivWidth, real k);

};

#endif /* PARTICLEPLANE_H_ */
