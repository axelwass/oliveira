/*
 * FinitePlane.cpp
 *
 *  Created on: Mar 25, 2011
 *      Author: mariano
 */

#include "../../include/shape/FinitePlane.h"
#include "../../include/shape/Sphere.h"
#include "../../include/shape/Cube.h"

FinitePlane::FinitePlane(real w, real h) {
	this->width = w;
	this->height = h;
	this->u = Vector3(1, 0, 0);
	this->v = Vector3(0, 0, 1);

	normal = v % u;
}

void FinitePlane::setRotation(const Vector3& r) {

	this->u = Vector3(1, 0, 0);
	this->v = Vector3(0, 0, 1);
	this->normal = Vector3(0, 1, 0);

	this->rotation = r;

	// And apply this one
	Matrix t = Matrix::getRotationMatrix(r.getX(), r.getY(), r.getZ());

	Vector3 resultU = t * u;
	Vector3 resultV = t * v;

	u = resultU;
	v = resultV;
	normal = u % v;
}

Shape::shapeType FinitePlane::getType() const {
	return PLANE;
}

// Test intersection between this shape and other
// and return the shape of its intersection (point, line, circle, etc)
IntersectionData FinitePlane::intersection(const Shape * s) {
	switch (s->getType()) {
	case SPHERE:
		return intersection((Sphere*) s);
	case CUBE:
		return intersection((Cube *) s);
	case PLANE:
		return IntersectionData();
	case NULLSHAPE:
		return IntersectionData();
	}
}

real FinitePlane::getWidth() const {
	return width;
}

real FinitePlane::getHeight() const {
	return height;
}

Vector3 FinitePlane::getU() const {
	return u;
}

Vector3 FinitePlane::getV() const {
	return v;
}

// For now, just work as infinite plane!
IntersectionData FinitePlane::intersection(const Cube * c) {

	Vector3 cPos = c->getPosition();

	real length = c->getLength();
	real dU = fabs(length * normal.scalarProduct(c->getU()));
	real dV = fabs(length * normal.scalarProduct(c->getV()));
	real dN = fabs(length * normal.scalarProduct(c->getN()));

	Vector3 difference = this->position - cPos;
	real d = normal.scalarProduct(difference);
	// Point of intersection
	Vector3 p = normal * d;

	if (fabs(d) <= dU + dV + dN)
		return IntersectionData(p, normal, difference.magnitude()); // If border is hit, consider as full hit

	return IntersectionData();
}

// For now, just return center of intersection (ignore circle)
IntersectionData FinitePlane::intersection(const Sphere * s) {

	// Sphere position
	Vector3 sPos = s->getPosition();

	// Plane position considering sphere as center of coordinate system
	Vector3 translated = this->position - sPos;

	// if a(x-tx) + b(y-ty) + c(z-tz) = 0
	// then d = atx - bty - ctz
	// d is distance to origin
	real d = normal.scalarProduct(translated);

	if (fabs(d) <= s->getRadius()) {

		// IMPORTANT!
		/*  In this case, we already have intersection.
		 * So we want to check if it falls between the boundaries of the plane.
		 * To do this we see if the projection of the point of intersection
		 * over both vectors (u,v) falls between the edges of the plane,
		 * considering also that the point is always going to fall
		 * inside the sphere, so we must add enough to translate that point
		 * to the surface of the sphere, getting the closest point to the edges of
		 * the plane.
		 */

		// Point of intersection
		Vector3 p = normal * d;

		// Translate it back to its original position
		p += translated;

		// Now let's check if point falls in finite area
		// u, v MUST be normalized, magnitude is 1
		Vector3 uProjection = u * (p * u);
		Vector3 vProjection = v * (p * v);

		real uDist = uProjection.magnitude();
		real vDist = vProjection.magnitude();

		real r = s->getRadius();
		real halfWidth = this->width / 2.0;
		real halfHeight = this->height / 2.0;

		// We must resolve corners (because (r^2 != (r^2 + r^2)))
		uDist = uDist < halfWidth ? 0 : uDist - halfWidth;
		vDist = vDist < halfHeight ? 0 : vDist - halfHeight;

		// Remember, d is distance to plane ( would be nDist )
		Vector3 totalDistance(uDist, d, vDist);

		if (totalDistance.magnitude() <= r)
			return IntersectionData(p, normal, d); // If border is hit, consider as full hit
	}

	return IntersectionData(fabs(d) - s->getRadius() * s->getScale().getX(), normal);
}
