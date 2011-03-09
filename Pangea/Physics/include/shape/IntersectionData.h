/*
 * CollisionData.h
 *
 *  Created on: Feb 14, 2011
 *      Author: mmerchan
 */

#include "../Vector3.h"

#ifndef COLLISIONDATA_H_
#define COLLISIONDATA_H_

class IntersectionData {

	private:
		Vector3 point;
		Vector3 normal;

		bool intersected;

	public:
		IntersectionData() {
			intersected = false;
		}

		IntersectionData(Vector3 point, Vector3 normal) {
			this->point = point;
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
};

#endif /* COLLISIONDATA_H_ */
