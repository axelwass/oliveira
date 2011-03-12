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
	gluPerspective(angle, 2, nearClip, farClip);

	Vector3 interestPoint = position + u * distance;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.getX(), position.getY(), position.getZ(),
			interestPoint.getX(), interestPoint.getY(), interestPoint.getZ(),
			n.getX(), n.getY(), n.getZ());
}

void PerspectiveCamera::setRotation(const Vector3& r) {

	// Set original u,v,n state ( Align with x,y,z axis )
	u = Vector3(1, 0, 0); // U is direction
	v = Vector3(0, 0, 1);
	n = Vector3(0, 1, 0); // Up vector

	// And apply this rotation
	Matrix t = Matrix::getRotationMatrix(r.getX(), r.getY(), r.getZ());
	u = t * u;
	v = t * v;
	n = t * n;

	this->rotation = r;
}

void PerspectiveCamera::rotate(const Vector3& r) {

	// Set original u,v,n state ( Align with x,y,z axis )
	u = Vector3(1, 0, 0); // U is direction
	v = Vector3(0, 0, 1);
	n = Vector3(0, 1, 0); // Up vector

	// Apply desired rotation
	Matrix t = Matrix::getRotationMatrix(r.getX(), r.getY(), r.getZ());
	u = t * u;
	v = t * v;
	n = t * n;

	// Apply inverse, get back
	Matrix inv = Matrix::getRotationMatrix(rotation.getX(), rotation.getY(),
			rotation.getZ());
	u = inv * u;
	v = inv * v;
	n = inv * n;

	this->rotation += r;
}

