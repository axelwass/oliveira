/*
 * Mesh.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include "../../include/Mesh/Mesh.h"

void Mesh::addFace(Face * face) {
	this->faces.push_back(face);
}

void Mesh::addVertex(Vertex * vertex) {
	this->vertices.push_back(vertex);
}

list<Vertex *> * Mesh::getVertices() {
	return &vertices;
}
list<Face *> * Mesh::getFaces() {
	return &faces;
}
