/*
 * Camera.h
 *
 *  Created on: Mar 11, 2011
 *      Author: mmerchan
 */

#include "../../../Generic/Generic.h"
#include "../../../Events/Events.h"

#ifndef CAMERA_H_
#define CAMERA_H_

// Plain interface

class Camera {
public:
	Camera() {
	}

	virtual ~Camera() {
	}

	virtual void render() = 0;
};

#endif /* CAMERA_H_ */
