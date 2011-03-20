/*
 * Transform.cpp
 *
 *  Created on: Mar 19, 2011
 *      Author: mmerchan
 */

#include "../../include/Mesh/Transform.h"

Transform::Transform(const Vector3& p, const Vector3& r, const Vector3& s) {
	this->position = p;
	this->rotation = r;
	this->scale = s;
}

void Transform::setPosition(const Vector3& position) {
	this->position = position;
}

void Transform::setRotation(const Vector3& rotation) {
	this->rotation = rotation;
}

void Transform::setScale(const Vector3& scale) {
	this->scale = scale;
}

Vector3 Transform::getPosition() const {
	return position;
}

Vector3 Transform::getRotation() const {
	return rotation;
}

Vector3 Transform::getScale() const {
	return scale;
}
