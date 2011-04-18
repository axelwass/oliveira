/*
 * Sphere.h
 *
 *  Created on: Jan 29, 2011
 *      Author: mmerchan
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Shape.h"
#include "FinitePlane.h"

#include <tr1/memory>

class Sphere;

typedef tr1::shared_ptr<Sphere> SpherePtr;

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

	void setRadius(real r) {
		this->radius = r;
	}

	// Test intersection between this shape and other
	// and return the shape of its intersection (point, line, circle, etc)
	virtual IntersectionData intersection(const Shape * s) {
		switch (s->getType()) {
		case SPHERE:
			return intersection((Sphere*) s);
		case CUBE:
			return IntersectionData();
		case PLANE:
			return ((FinitePlane *) s)->intersection(this);
		case NULLSHAPE:
			return IntersectionData();
		}
		return IntersectionData();
	}

	IntersectionData intersection(const Sphere * s) {
		Vector3 distance = s->position - this->position;
		Vector3 normal = distance;
		normal.normalize();

		if (distance.magnitude() - (this->radius * scale.getX()) - (s->radius
				* s->scale.getX()) <= 0) {
			// Return distance normalized... normal of collision
			return IntersectionData(this->position + (normal * this->radius
					* scale.getX()), normal, distance.magnitude() - (s->radius
							* s->scale.getX()) - (radius * scale.getX()));
		} else
			// Not collided, return distance to collision
			return IntersectionData(distance.magnitude() - (s->radius
					* s->scale.getX()) - (radius * scale.getX()), normal);
	}
};

#endif /* SPHERE_H_ */
