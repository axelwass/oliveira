/*
 * Positionable.h
 *
 *  Created on: Jan 26, 2011
 *      Author: mmerchan
 */

#include "../../Generic/Generic.h"

#ifndef POSITIONABLE_H_
#define POSITIONABLE_H_

// Interface for any space partitioning algorithm such as octree, kdtree, quadtree, bsp, etc.
template<class T>
class Positionable {
	public:
		Positionable() {
		}

		virtual Vector3 getPosition() = 0;

		// ESTO DEBERIA SER UN SHARED_PTR
		// I hate this
		virtual T * getThis() = 0;
};

#endif /* POSITIONABLE_H_ */
