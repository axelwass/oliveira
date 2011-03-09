/*
 * Cube.h
 *
 *  Created on: Jan 30, 2011
 *      Author: mmerchan
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "../../../Generic/Generic.h"
#include "Sphere.h"
#include <tr1/memory>
using namespace std;

class Cube;

typedef tr1::shared_ptr<Cube> CubePtr;

// For now just a cube. its very easy to extend it to a box with depth,width and height
class Cube: public Shape {
	private:
		real length;
		Vector3 u, v, n; // local space versors

	public:
		Cube(real length) {
			this->length = length;
			this->u = Vector3(1, 0, 0);
			this->v = Vector3(0, 0, 1);
			this->n = Vector3(0, 1, 0);
		}

		real getLength() const {
			return length;
		}

		void setLength(const real& length){
			this->length = length;
		}

		shapeType getType() const {
			return CUBE;
		}

		void setRotation(const Vector3& r) {
			// Erase previous rotation
			Matrix prev = Matrix::getRotationMatrix(-rotation.getX(),
					-rotation.getY(), -rotation.getZ());

			u = prev * u;
			v = prev * v;
			n = prev * n;

			this->rotation = r;

			// And apply this one
			Matrix t = Matrix::getRotationMatrix(r.getX(), r.getY(), r.getZ());

			u = t * u;
			v = t * v;
			n = t * n;
		}

		// Test intersection between this shape and other
		// and return the shape of its intersection (point, line, circle, etc)
		IntersectionData intersection(const Shape * s) {
			switch (s->getType()) {
			case SPHERE:
				return intersection((Sphere*) s);
			case CUBE:
				return IntersectionData();
			case PLANE:
				return IntersectionData();
			case NULLSHAPE:
				return IntersectionData();
			}
		}

		// Cube-Sphere
		IntersectionData intersection(const Sphere * s) {

			Vector3 distance = s->getPosition() - this->getPosition();

			Vector3 uP, vP, nP; // projections of distance into local space
			uP = u * (distance * u);
			vP = v * (distance * v);
			nP = n * (distance * n);

			// Mangitudes of those projections
			real uDist, vDist, nDist;
			uDist = uP.magnitude();
			vDist = vP.magnitude();
			nDist = nP.magnitude();

			real halfLength = length / 2;

			// Now check if sphere lays inside box
			uDist = uDist < halfLength ? 0 : uDist - halfLength;
			vDist = vDist < halfLength ? 0 : vDist - halfLength;
			nDist = nDist < halfLength ? 0 : nDist - halfLength;

			Vector3 totalDistance(uDist, vDist, nDist);

			if (totalDistance.magnitude() <= s->getRadius()) {

				totalDistance.normalize();

				// dont know point yet..
				return IntersectionData(Vector3(), totalDistance);
			} else
				return IntersectionData();
		}
};

#endif /* CUBE_H_ */
