/*
 * Camera.cpp
 *
 *  Created on: Mar 11, 2010
 *      Author: mmerchan
 */

#include "../../include/Camera/PerspectiveCamera.h"

void PerspectiveCamera::render() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, 2, .1, 5000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(position.getX(), position.getY(), position.getZ(),
			interestPoint.getX(), interestPoint.getY(), interestPoint.getZ(),
			upVector.getX(), upVector.getY(), upVector.getZ());
}

