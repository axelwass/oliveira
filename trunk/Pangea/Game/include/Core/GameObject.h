/*
 * GameObject.h
 *
 *  Created on: Mar 26, 2011
 *      Author: mariano
 */

#include "../GameEngine.h"

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

class GameObject {
protected:

	// physAdapter
	// gfxAdapter

public:
	GameObject() {
	}
	virtual ~GameObject() {
	}
	virtual void process() = 0;
};

#endif /* GAMEOBJECT_H_ */
