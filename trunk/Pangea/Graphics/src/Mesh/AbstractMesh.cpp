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

MeshRenderer * AbstractMesh::getRenderer() {
	return this->renderer;
}

void AbstractMesh::render() {
	this->renderer->render();
}

Transform * AbstractMesh::getTransform() {
	return &transform;
}

void AbstractMesh::setPivot(const Vector3& p) {
	this->pivot = p;
}

Vector3 AbstractMesh::getPivot() const {
	return pivot;
}

void AbstractMesh::applyTransform() {

	vector<Vertex *> * vList = getVertices();
	vector<Vertex *>::iterator v;
	for (v = vList->begin(); v != vList->end(); v++) {
		Vector3 p = (*v)->getPosition() + transform.getPosition();
		(*v)->setPosition(p);
	}

	transform.setPosition(Vector3());
}
