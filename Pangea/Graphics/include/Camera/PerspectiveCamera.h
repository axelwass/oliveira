/*
 * Camera.h
 *
 *  Created on: Mar 11, 2010
 *      Author: mmerchan
 */

#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_

#include <SDL/SDL.h>
#include "Camera.h"
#include "../../../Generic/Generic.h"
#include "../../../Events/Events.h"
#include <GL/glut.h>

/**
 * Simple orbit camera with aim and up
 */
class PerspectiveCamera: public MouseListener, public Camera {

private:

	Vector3 position;
	Vector3 interestPoint;
	Vector3 upVector;
	float distance;
	float angle;
	float zoomSensitivity;
	bool active;

public:

	PerspectiveCamera(const float& distance, const Vector3& interestPoint, float angle) {
		this->distance = distance;
		this->interestPoint = interestPoint;
		this->angle = angle;
		this->active = true;

		upVector = Vector3(0, 1, 0);
		zoomSensitivity = 15;
	}

	void reshape(int w, int h) {
		glViewport(0, 0, w, h);
	}

	void render();

	void onMouseLeftClickDown() {
		active = false;
	}

	void onMouseMotion(int x, int y) {
		if (active) {
			float theta = .01 + x * 3.1415 / 360;
			float phi = y * 3.1415 / 360;

			if (phi > 3.14)
				phi = 3.14;

			position = interestPoint + Vector3(
					distance * cos(theta) * sin(phi), -distance * cos(phi),
					distance * sin(theta) * sin(phi));
		}
	}

	void setZoomSensitivity(float s) {
		this->zoomSensitivity = s;
	}

	void onMouseWheelDown() {

		Vector3 dir = interestPoint - position;
		dir.normalize();

		distance -= zoomSensitivity;
		position += dir * zoomSensitivity;

	}

	void onMouseWheelUp() {
		Vector3 dir = interestPoint - position;
		dir.normalize();

		distance += zoomSensitivity;
		position -= dir * zoomSensitivity;
	}

};

#endif /* PERSPECTIVECAMERA_H_ */
