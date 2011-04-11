/*
 * MeshCube.h
 *
 *  Created on: Apr 10, 2011
 *      Author: mariano
 */

#ifndef MESHCUBE_H_
#define MESHCUBE_H_

class MeshCube: public Mesh {

private:

	void addCubePlane(Vector3 p, Vector3 u, Vector3 v) {
		u.normalize();
		v.normalize();
		Vector3 n = v % u;

		int v1 = addVertex(new Vertex(p + u * -.5 + v * -.5));
		int v2 = addVertex(new Vertex(p + u * -.5 + v * .5));
		int v3 = addVertex(new Vertex(p + u * .5 + v * .5));
		int v4 = addVertex(new Vertex(p + u * .5 + v * -.5));

		int t1 = addTextureCoordinate(Vector3(0, 0, 0));
		int t2 = addTextureCoordinate(Vector3(0, 1, 0));
		int t3 = addTextureCoordinate(Vector3(1, 1, 0));
		int t4 = addTextureCoordinate(Vector3(1, 0, 0));

		int nIndex = addVertexNormal(n);

		Face * f = new Face();
		f->addVertex(v1, nIndex, t1);
		f->addVertex(v2, nIndex, t2);
		f->addVertex(v3, nIndex, t3);
		f->addVertex(v4, nIndex, t4);

		addFace(f);
	}

public:
	MeshCube() {
		addCubePlane(Vector3(.5, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, -1));
		addCubePlane(Vector3(-.5, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));
		addCubePlane(Vector3(0, .5, 0), Vector3(1, 0, 0), Vector3(0, 0, -1));
		addCubePlane(Vector3(0, -.5, 0), Vector3(1, 0, 0), Vector3(0, 0, 1));
		addCubePlane(Vector3(0, 0, .5), Vector3(1, 0, 0), Vector3(0, -1, 0));
		addCubePlane(Vector3(0, 0, -.5), Vector3(1, 0, 0), Vector3(0, 1, 0));
	}

};

#endif /* MESHCUBE_H_ */
