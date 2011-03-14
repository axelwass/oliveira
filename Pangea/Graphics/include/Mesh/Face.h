/*
 * Face.h
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include <list>
#include "../../../Generic/Generic.h"
#include "Vertex.h"

using namespace std;

#ifndef FACE_H_
#define FACE_H_

class Face {

private:

	list<Vertex *> vertices;
	Vector3 normal;

public:
	void addVertex(Vertex * v);

	void setNormal(const Vector3& normal);

	Vector3 getNormal();

	void updateNormal();

	list<Vertex *> getVertices();

};

#endif /* FACE_H_ */
