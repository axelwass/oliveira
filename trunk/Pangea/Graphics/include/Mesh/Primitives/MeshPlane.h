/*
 * MeshPlane.h
 *
 *  Created on: Mar 25, 2011
 *      Author: mariano
 */

#ifndef MESHPLANE_H_
#define MESHPLANE_H_

class MeshPlane: public Mesh {
public:
	MeshPlane() {

		addVertex(new Vertex(Vector3(-1, 0, -1)));
		addVertex(new Vertex(Vector3(-1, 0, 1)));
		addVertex(new Vertex(Vector3(1, 0, 1)));
		addVertex(new Vertex(Vector3(1, 0, -1)));

		addVertexNormal(Vector3(0, 1, 0));

		Face * f = new Face();
		f->addVertex(0, 0, -1);
		f->addVertex(1, 0, -1);
		f->addVertex(2, 0, -1);
		f->addVertex(3, 0, -1);

		addFace(f);
	}
};

#endif /* MESHPLANE_H_ */
