/*
 * Sphere.h
 *
 *  Created on: Jan 29, 2011
 *      Author: mmerchan
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Shape.h"
#include "NullShape.h"
#include "../precision.h"

class Sphere: public Shape {
	private:
		real radius;
	public:
		Sphere(real r) {
			this->radius = r;
		}

		shapeType getType() const {
			return SPHERE;
		}

		real getRadius() const {
			return this->radius;
		}

		// Test intersection between this shape and other
		// and return the shape of its intersection (point, line, circle, etc)
		virtual Shape * intersection(const Shape * s) {
			switch (s->getType()) {
			case SPHERE:
				return intersection((Sphere*) s);
			case CUBE:
				return NULL;
			case PLANE:
				return NULL;
			case NULLSHAPE:
				return NULL;
			}
			return NullShape::getInstance();
		}

		Shape * intersection(const Sphere * s) {

			Vector3 distance = s->position - this->position;

			if (distance.magnitude() - this->radius - s->radius < 0) {
				// Return distance normalized... normal of collision
				return this;
			} else
				return NULL;
		}
};

#endif /* SPHERE_H_ */
