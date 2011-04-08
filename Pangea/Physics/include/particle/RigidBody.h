/*
 * RigidBody.h
 *
 *  Created on: Mar 25, 2011
 *      Author: mariano
 */

#include "Particle.h"
#include "../shape/Shape.h"

#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

class RigidBody: public Particle {
private:
	ShapePtr shape;
public:

	// por ahora cuerpos de masa infinita y estaticos!!!! TODO
	RigidBody(ShapePtr s) :
		Particle(s->getPosition(), 0) {
		this->shape = s;

	//	printf("RG: %g,%g,%g\n", getPosition().getX(),getPosition().getY(),getPosition().getZ());
	}

	virtual ShapePtr getCollisionShape() {
		shape->setPosition(this->data.getPosition());
		return shape;
	}

	CollisionableType getCollisionableType() {
		return C_RigidBody;
	}

};

#endif /* RIGIDBODY_H_ */
