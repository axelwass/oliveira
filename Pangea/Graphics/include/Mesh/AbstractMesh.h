/*
 * AbstractMesh.h
 *
 *  Created on: Aug 3, 2010
 *      Author: mmerchan
 */
#include "../../../Generic/Generic.h"

#include "Vertex.h"
#include "Face.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include <vector>

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

		Transform transform;
		Vector3 pivot;
		MeshRenderer * renderer;

	public:

		AbstractMesh();

		void setRenderer(MeshRenderer * mr);
		void setPivot(const Vector3& p);

		Vector3 getPivot() const;
		MeshRenderer * getRenderer();
		Transform * getTransform();

		void render();
		void applyTransform();

		virtual int addVertex(Vertex * vertex) = 0;
		virtual void addFace(Face * face) = 0;


		virtual vector<Vector3>& getTextureCoordinates() = 0;
		virtual vector<Vector3>& getNormals() = 0;
		virtual vector<Vertex *> * getVertices() = 0;
		virtual vector<Face *> * getFaces() = 0;
};

#endif /* ABSTRACTMESH_H_ */
