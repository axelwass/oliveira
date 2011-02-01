/*
 * FinitePlane.h
 *
 *  Created on: Jan 29, 2011
 *      Author: mmerchan
 */

#include "../precision.h"
#include "../Matrix.h"
#include "NullShape.h"
#include "Sphere.h"

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

		FinitePlane(real w, real h) {
			this->width = w;
			this->height = h;
			this->u = Vector3(1, 0, 0);
			this->v = Vector3(0, 0, 1);

			normal = v % u;

			printf("(%g,%g,%g)\n", normal.getX(), normal.getY(), normal.getZ());
		}

		void setRotation(const Vector3& r) {

			// Erase previous rotation
			Matrix prev = Matrix::getRotationMatrix(-rotation.getX(),
					-rotation.getY(), -rotation.getZ());

			u = prev * u;
			v = prev * v;

			this->rotation = r;

			// And apply this one
			Matrix t = Matrix::getRotationMatrix(r.getX(), r.getY(), r.getZ());

			Vector3 resultU = t * u;
			Vector3 resultV = t * v;

			u = resultU;
			v = resultV;
			normal = u % v;

		}

		shapeType getType() const {
			return PLANE;
		}

		// Test intersection between this shape and other
		// and return the shape of its intersection (point, line, circle, etc)
		Shape * intersection(const Shape * s) {
			printf("otra\n");

			return NULL;
		}

		real getWidth() const {
			return width;
		}

		real getHeight() const {
			return height;
		}

		Vector3 getU() const {
			return u;
		}

		Vector3 getV() const {
			return v;
		}

		// For now, just return center of intersection (ignore circle)
		Shape * intersection(const Sphere *s) {

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
				Vector3 totalDistance(uDist, vDist, d);

				//printf("u:%g, v:%g, n:%g\n", uDist, vDist, d);

				if (totalDistance.magnitude() <= r)
					return this;
			}

			return NULL;
		}
};

#endif /* FINITEPLANE_H_ */
