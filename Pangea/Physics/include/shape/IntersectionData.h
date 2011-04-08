/*
 * CollisionData.h
 *
 *  Created on: Feb 14, 2011
 *      Author: mmerchan
 */

#include "../../../Generic/Generic.h"

#ifndef COLLISIONDATA_H_
#define COLLISIONDATA_H_

class IntersectionData {

	private:
		Vector3 point;
		Vector3 normal;
		Vector3 distance; // between elements, for repositioning

		bool intersected;

	public:
		IntersectionData() {
			intersected = false;
		}

		IntersectionData(Vector3 point, Vector3 normal, Vector3 distance) {
			this->point = point;
			this->distance = distance;
			this->normal = normal;
			this->normal.normalize();
			intersected = true;
		}

		bool hasIntersected() {
			return intersected;
		}

		Vector3 getPoint() {
			return point;
		}

		Vector3 getNormal() {
			return normal;
		}

		Vector3 getDistance() {
			return distance;
		}
};

#endif /* COLLISIONDATA_H_ */
