/*
 * AbstractMesh.h
 *
 *  Created on: Aug 3, 2010
 *      Author: mmerchan
 */
#include "../../../Generic/Generic.h"

#include "Vertex.h"
#include "Face.h"
#include "MeshRenderer.h"

using namespace std;

#ifndef ABSTRACTMESH_H_
#define ABSTRACTMESH_H_

/**
 * The idea is not having to worry about mesh algorithm implementation right here.
 * The only requirement is returning the mesh data in a std::list
 * Initially, it doesn't render unless you assign it a real renderer.
 * It has a null renderer at construction.
 */
class AbstractMesh {
	private:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

		MeshRenderer * renderer;

	public:

		AbstractMesh();

		void setRenderer(MeshRenderer * mr);
		MeshRenderer * getRenderer();
		void render();

		void rotate(const Vector3& r);
		void translate(const Vector3& t);

		void setPosition(const Vector3& position);
		void setRotation(const Vector3& rotation);
		void setScale(const Vector3& scale);

		Vector3 getPosition();
		Vector3 getRotation();
		Vector3 getScale();

		virtual void addVertex(Vertex * vertex) = 0;
		virtual void addFace(Face * face) = 0;

		virtual list<Vertex *> * getVertices() = 0;
		virtual list<Face *> * getFaces() = 0;
};

#endif /* ABSTRACTMESH_H_ */
