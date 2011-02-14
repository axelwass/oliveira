/*
 * Collisionable.h
 *
 *  Created on: Feb 14, 2011
 *      Author: mmerchan
 */

#include "../shape/Shape.h"
#include "../shape/IntersectionData.h"

#ifndef COLLISIONABLE_H_
#define COLLISIONABLE_H_

class Collisionable {
	public:
		virtual ~Collisionable() {
		}

		virtual IntersectionData checkCollision(Collisionable& other) = 0;

		virtual bool resolveCollision(Collisionable& other, IntersectionData& data) = 0;

		virtual ShapePtr getCollisionShape() = 0;
};

#endif /* COLLISIONABLE_H_ */
