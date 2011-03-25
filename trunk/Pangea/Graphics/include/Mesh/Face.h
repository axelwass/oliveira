/*
 * Face.h
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include <list>
#include "../../../Generic/Generic.h"
#include "Vertex.h"
#include <vector>

using namespace std;

#ifndef FACE_H_
#define FACE_H_

class VertexWrapper {
private:
	int vertexIndex;
	int normalIndex;
	int txIndex;
public:
	VertexWrapper(int v, int n, int t) :
		vertexIndex(v), normalIndex(n), txIndex(t) {
	}

	int getVertex() {
		return vertexIndex;
	}

	int getNormal() {
		return normalIndex;
	}

	int getTexture() {
		return txIndex;
	}
};

class Face {

private:

	vector<VertexWrapper> vertices;

	Vector3 normal;

public:

	Face() {
	}

	void addVertex(int vertex, int normal, int txCoordiante) {
		vertices.push_back(VertexWrapper(vertex, normal, txCoordiante));
	}

	Vector3 getNormal();

	void updateNormal();

	vector<VertexWrapper>& getVertices() {
		return vertices;
	}

};

#endif /* FACE_H_ */
