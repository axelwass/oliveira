/*
 * FinitePlane.h
 *
 *  Created on: Jan 29, 2011
 *      Author: mmerchan
 */

#include "../../../Generic/Generic.h"
#include "Shape.h"

class Sphere;

#ifndef FINITEPLANE_H_
#define FINITEPLANE_H_

class FinitePlane: public Shape {
private:
	typedef Shape super;

	real width;
	real height;

	Vector3 u, v;
	Vector3 normal;

public:

	FinitePlane(real w, real h);

	void setRotation(const Vector3& r);

	shapeType getType() const;

	// Test intersection between this shape and other
	// and return the shape of its intersection (point, line, circle, etc)
	IntersectionData intersection(const Shape * s);

	real getWidth() const;

	real getHeight() const;

	Vector3 getU() const;

	Vector3 getV() const;

	// For now, just return center of intersection (ignore circle)
	IntersectionData intersection(const Sphere * s);
};

#endif /* FINITEPLANE_H_ */
