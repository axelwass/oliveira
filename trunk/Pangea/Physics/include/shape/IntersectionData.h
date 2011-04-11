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
	real distance; // between elements, for repositioning

	bool intersected;

public:
	IntersectionData() {
		intersected = false;
	}

	IntersectionData(real distance, Vector3 normal) {
		intersected = false;
		this->distance = distance;
		this->normal = normal;
	}

	IntersectionData(Vector3 point, Vector3 normal, real distance) {
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

	real getDistance() {
		return distance;
	}
};

#endif /* COLLISIONDATA_H_ */
