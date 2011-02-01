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
			return NullShape::getInstance();
		}
};

#endif /* SPHERE_H_ */
