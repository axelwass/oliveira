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

		addVertex(new Vertex(Vector3(-.5, 0, -.5)));
		addVertex(new Vertex(Vector3(-.5, 0, .5)));
		addVertex(new Vertex(Vector3(.5, 0, .5)));
		addVertex(new Vertex(Vector3(.5, 0, -.5)));

		addTextureCoordinate(Vector3(0,0,0));
		addTextureCoordinate(Vector3(0,1,0));
		addTextureCoordinate(Vector3(1,1,0));
		addTextureCoordinate(Vector3(1,0,0));

		addVertexNormal(Vector3(0, 1, 0));

		Face * f = new Face();
		f->addVertex(0, 0, 0);
		f->addVertex(1, 0, 1);
		f->addVertex(2, 0, 2);
		f->addVertex(3, 0, 3);

		addFace(f);
	}
};

#endif /* MESHPLANE_H_ */