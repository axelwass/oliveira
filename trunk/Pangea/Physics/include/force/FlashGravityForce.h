/*
 * FlashGravityForce.h
 *
 *  Created on: Nov 8, 2010
 *      Author: mmerchan
 */

#include <stdlib.h>

#ifndef FLASHGRAVITYFORCE_H_
#define FLASHGRAVITYFORCE_H_

class FlashGravityForce: public InterParticleForce {
private:

	FlashGravityForce(Particle * other) :
		InterParticleForce(other) {
	}

	// Evaluation function
	DerivativeData _evaluate(real t, ParticleData * data) {

		Vector3 dir1 = other->getData().getPosition() - data->getPosition();

		Vector3 dir(dir1.getY(), -dir1.getX(), 0);

		dir += dir1 * 50;

		real r = dir.magnitude();
		dir.normalize();

		Vector3 acc = dir * (other->getData().getMass() * r * r * r
				* 0.0000000001);

		return DerivativeData(acc);
	}

	Force * _clone() {
		return new FlashGravityForce(this->other);
	}

public:
	FlashGravityForce() {
	}

	virtual ~FlashGravityForce() {
	}

	InterParticleForce * getFunctionCopy() {
		return new FlashGravityForce(this->other);
	}
};

#endif /* FLASHGRAVITYFORCE_H_ */
