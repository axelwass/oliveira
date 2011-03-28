/*
 * StaticObject.h
 *
 *  Created on: Mar 26, 2011
 *      Author: mariano
 */
#include "../Core/GameObject.h"

#ifndef STATICOBJECT_H_
#define STATICOBJECT_H_

class StaticObject: public GameObject {
protected:

	Mesh * mesh;
	Particle * body;

public:
	StaticObject(Mesh * m, Particle * b) :
		mesh(m), body(b) {
	}

	void process() {
		mesh->getTransform()->setPosition(body->getPosition());
		mesh->getTransform()->setRotation(
				body->getCollisionShape()->getRotation());
	}
};

#endif /* STATICOBJECT_H_ */
