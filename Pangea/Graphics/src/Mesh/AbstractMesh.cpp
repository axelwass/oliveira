/*
 * AbstractMesh.cpp
 *
 *  Created on: Aug 3, 2010
 *      Author: mmerchan
 */

#include "../../include/Mesh/AbstractMesh.h"
#include "../../include/Mesh/NullMeshRenderer.h"

AbstractMesh::AbstractMesh() {
	this->setRenderer(new NullMeshRenderer(this));
}

void AbstractMesh::setRenderer(MeshRenderer * mr) {
	this->renderer = mr;
}


MeshRenderer * AbstractMesh::getRenderer(){
	return this->renderer;
}

void AbstractMesh::render() {
	this->renderer->render();
}

void AbstractMesh::setPosition(const Vector3& position) {
	this->position = position;
}

void AbstractMesh::setRotation(const Vector3& rotation) {
	this->rotation = rotation;
}

void AbstractMesh::setScale(const Vector3& scale) {
	this->scale = scale;
}

Vector3 AbstractMesh::getPosition() {
	return position;
}

Vector3 AbstractMesh::getRotation() {
	return rotation;
}

Vector3 AbstractMesh::getScale() {
	return scale;
}

void AbstractMesh::rotate(const Vector3& r) {
	this->rotation += r;
}

void AbstractMesh::translate(const Vector3& t) {
	this->position += t;
}
