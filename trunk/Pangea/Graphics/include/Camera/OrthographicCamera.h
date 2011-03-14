/*
 * OrthographicCamera.h
 *
 *  Created on: Mar 12, 2011
 *      Author: mmerchan
 */

#include <GL/gl.h>
#include "Camera.h"

#ifndef ORTHOGRAPHICCAMERA_H_
#define ORTHOGRAPHICCAMERA_H_

class OrthographicCamera: public Camera {

	private:

		real nearClip, farClip;
		real left, right, bottom, top;

	public:
		OrthographicCamera(real nearClip, real farClip, real left, real right,
				real bottom, real top) :
			nearClip(nearClip), farClip(farClip), left(left), right(right),
					bottom(bottom), top(top) {

		}

		void render() {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(left, right, bottom, top, nearClip, farClip);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
};

#endif /* ORTHOGRAPHICCAMERA_H_ */
