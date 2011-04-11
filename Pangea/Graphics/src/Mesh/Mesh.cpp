/*
 * Mesh.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include <stdio.h>
#include "../../include/Mesh/Mesh.h"

void Mesh::addFace(Face * face) {
	this->faces.push_back(face);
}

int Mesh::addVertex(Vertex * vertex) {
	this->vertices.push_back(vertex);
	return vertices.size()-1;
}

int Mesh::addVertexNormal(Vector3 n) {
	this->normals.push_back(n);
	return normals.size()-1;
}

int Mesh::addTextureCoordinate(Vector3 t) {
	this->txCoords.push_back(t);
	return txCoords.size()-1;
}

vector<Vertex *> * Mesh::getVertices() {
	return &vertices;
}

vector<Vector3>& Mesh::getTextureCoordinates() {
	return txCoords;
}

vector<Vector3>& Mesh::getNormals() {
	return normals;
}

vector<Face *> * Mesh::getFaces() {
	return &faces;
}

void Mesh::centerPivot() {
	Vector3 pivot;

	vector<Vertex *>::iterator v;
	for (v = vertices.begin(); v != vertices.end(); v++)
		pivot += (*v)->getPosition();

	if (vertices.size())
		pivot *= (1.0 / vertices.size());

	setPivot(pivot);

}
