/*
 * WalkthroughCamera.h
 *
 *  Created on: Mar 12, 2011
 *      Author: mmerchan
 */

#include "PerspectiveCamera.h"
#include "../../../Events/Events.h"

#ifndef WALKTHROUGHCAMERA_H_
#define WALKTHROUGHCAMERA_H_

class WalkthroughCamera: public PerspectiveCamera,
		public MouseListener,
		public KeyListener {

private:

	typedef PerspectiveCamera super;

	// Velocity values
	real frontVel, sideVel;
	real velocityMagnitude;

	bool active;

public:

	WalkthroughCamera(Vector3 pos, real farClip, real nearClip, real angle) :
		PerspectiveCamera(pos, farClip, nearClip, angle), MouseListener() {
		velocityMagnitude = 5;
		active = false;
	}

	void render() {

		Vector3 frontDispl = u;
		frontDispl.normalize();
		frontDispl *= frontVel;

		Vector3 sideDispl = v;
		sideDispl.normalize();
		sideDispl *= sideVel;

		position += frontDispl + sideDispl;

		super::render();
	}

	void onKeyUp(int key) {
		switch (key) {
		case 'a':
			sideVel -= -velocityMagnitude;
			break;
		case 'd':
			sideVel -= velocityMagnitude;
			break;
		case 'w':
			frontVel -= velocityMagnitude;
			break;
		case 's':
			frontVel -= -velocityMagnitude;
			break;
		}
	}

	void onKeyDown(int key) {
		switch (key) {
		case 'a':
			sideVel += -velocityMagnitude;
			break;
		case 'd':
			sideVel += velocityMagnitude;
			break;
		case 'w':
			frontVel += velocityMagnitude;
			break;
		case 's':
			frontVel += -velocityMagnitude;
			break;
		}
	}

	void onMouseMotion(MouseEvent event) {

		int x, y;
		x = event.getRelativeX();
		y = event.getRelativeY();

		if (!active)
			return;
		real yaw, pitch;
		yaw = x / 500.0;
		pitch = y / 500.0;
		rotate(Vector3(0, yaw, pitch));

	}

	void onMouseWheelDown(MouseEvent event) {
	}

	void onMouseWheelUp(MouseEvent event) {
	}

	void onMouseLeftClickDown(MouseEvent event) {
		active = true;
	}
	void onMouseLeftClickUp(MouseEvent event) {
		active = false;
	}

	void onMouseLeftClick(MouseEvent event) {
	}

};

#endif /* WALKTHROUGHCAMERA_H_ */
