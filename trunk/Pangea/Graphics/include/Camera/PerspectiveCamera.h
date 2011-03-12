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
#include <GL/glut.h>

/**
 * Perspective camera interface
 */
class PerspectiveCamera: public Camera {

	protected:

		Vector3 position;
		Vector3 rotation;
		Vector3 u, v, n;

		real distance;
		real farClip, nearClip;
		real angle;

	public:

		PerspectiveCamera(Vector3 pos, real farClip, real nearClip, real angle) {
			this->position = pos;
			this->farClip = farClip;
			this->nearClip = nearClip;
			this->angle = angle;

			this->distance = 1;

			// Local space vectors
			this->u = Vector3(1, 0, 0); // U is direction
			this->v = Vector3(0, 0, 1);
			this->n = Vector3(0, 1, 0); // Up vector
		}

		void render();

		void rotate(const Vector3& r);

		void setRotation(const Vector3& r);

		/*
		 void onMouseLeftClickDown() {
		 active = false;
		 }

		 void onMouseMotion(int x, int y) {
		 if (active) {
		 float theta = .01 + x * 3.1415 / 360;
		 float phi = y * 3.1415 / 360;

		 if (phi > 3.14)
		 phi = 3.14;

		 position = interestPoint + Vector3(distance * cos(theta) * sin(
		 phi), -distance * cos(phi), distance * sin(theta)
		 * sin(phi));
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
		 */
};

#endif /* PERSPECTIVECAMERA_H_ */
