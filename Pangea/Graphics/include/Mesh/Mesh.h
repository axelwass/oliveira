/*
 * Mesh.h
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include "AbstractMesh.h"
#include "Face.h"
using namespace std;

#ifndef MESH_H_
#define MESH_H_

class Mesh: public AbstractMesh {
	private:
		list<Vertex *> vertices;
		list<Face *> faces;

		typedef AbstractMesh super;

	public:

		Mesh() {
		}

		void addVertex(Vertex * vertex);
		void addFace(Face * face);

		list<Vertex *> * getVertices();
		list<Face *> * getFaces();

};

#endif /* MESH_H_ */
