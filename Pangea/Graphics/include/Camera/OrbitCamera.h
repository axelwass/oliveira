/*
 * OrbitCamera.h
 *
 *  Created on: Mar 12, 2011
 *      Author: mmerchan
 */

#include "PerspectiveCamera.h"
#include "../../../Events/Events.h"

#ifndef ORBITCAMERA_H_
#define ORBITCAMERA_H_

class OrbitCamera: public PerspectiveCamera, public MouseListener {

public:

	OrbitCamera(Vector3 pos, Vector3 interestPoint, real farClip,
			real nearClip, real angle) :
		PerspectiveCamera(pos, farClip, nearClip, angle) {
	}

	void onMouseRelativeMotion(int x, int y) {
	}

	void onMouseMotion(int x, int y) {
	}

	void onMouseWheelDown() {
	}

	void onMouseWheelUp() {
	}
};

#endif /* ORBITCAMERA_H_ */
