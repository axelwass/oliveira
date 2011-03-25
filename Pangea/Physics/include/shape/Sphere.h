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

		if (distance.magnitude() - this->radius - s->radius < 0) {
			Vector3 n = distance;
			n.normalize();
			// Return distance normalized... normal of collision
			return IntersectionData(this->position + (n * this->radius), n);
		} else
			return IntersectionData();
	}
};

#endif /* SPHERE_H_ */
