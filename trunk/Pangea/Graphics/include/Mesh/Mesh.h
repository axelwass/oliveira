/*
 * Mesh.h
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include "AbstractMesh.h"
#include "Face.h"
#include <vector>
using namespace std;

#ifndef MESH_H_
#define MESH_H_

class Mesh: public AbstractMesh {
	private:

		vector<Vertex *> vertices;
		vector<Vector3> normals;
		vector<Vector3> txCoords;
		vector<Face *> faces;

		typedef AbstractMesh super;

	public:

		Mesh() {
		}

		void centerPivot();

		void addVertex(Vertex * vertex);
		void addVertexNormal(Vector3 n);
		void addTextureCoordinate(Vector3 t);



		void addFace(Face * face);



		vector<Vector3>& getTextureCoordinates();
		vector<Vector3>& getNormals();
		vector<Vertex *> * getVertices();
		vector<Face *> * getFaces();

};

#endif /* MESH_H_ */
