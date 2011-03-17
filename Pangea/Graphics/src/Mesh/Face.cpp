/*
 * Face.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */
#include <stdio.h>
#include "../../include/Mesh/Face.h"

void Face::setNormal(const Vector3& normal) {
	this->normal = normal;
}

Vector3 Face::getNormal() {
	return normal;
}

void Face::updateNormal() {

	if (vertices.size() < 3)
		return;

	Vector3 v0 = vertices.front()->getPosition();
	Vector3 v1 = (*(++vertices.begin()))->getPosition();
	Vector3 v2 = (*(++(++vertices.begin())))->getPosition();

	Vector3 p1 = v1 - v0;
	Vector3 p2 = v2 - v1;

	normal = p1.vectorProduct(p2);
	normal.normalize();
/*

	list<Vertex *>::iterator v;
	for(v=vertices.begin();v!=vertices.end();v++){
		(*v)->updateNormal(normal);
	}*/

}

void Face::addVertex(Vertex * v) {
	this->vertices.push_back(v);
}

list<Vertex *> Face::getVertices() {
	return list<Vertex *> (vertices);
}

