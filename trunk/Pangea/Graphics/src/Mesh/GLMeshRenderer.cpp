/*
 * OpenGLMeshRenderer.cpp
 *
 *  Created on: Aug 3, 2010
 *      Author: mmerchan
 */

#include "../../include/Mesh/GLMeshRenderer.h"
#include "../../../Generic/Generic.h"
#include <GL/gl.h>
#include <stdio.h>

void GLMeshRenderer::render() {

	Vector3 p = mesh->getPosition();
	Vector3 r = mesh->getRotation();
	Vector3 s = mesh->getScale();

	//      Sets color to red
	glTranslatef(p.getX(), p.getY(), p.getZ());

	list<Face *>::iterator faceItr = mesh->getFaces()->begin();
	for (; faceItr != mesh->getFaces()->end(); faceItr++) {

		list<Vertex *> faceVertices = (*faceItr)->getVertices();
		list<Vertex *>::iterator vertexItr = faceVertices.begin();

		Vector3 normal;
		Vector3 vPos;

		glBegin(GL_POLYGON);
		for (vertexItr = faceVertices.begin(); vertexItr != faceVertices.end(); vertexItr++) {
			normal = (*faceItr)->getNormal();
			vPos = (*vertexItr)->getPosition().componentProduct(s);

			// Prevent normals from scaling
			glNormal3f(normal.getX(), normal.getY(), normal.getZ());
			glVertex3f(vPos.getX(), vPos.getY(), vPos.getZ());
		}
		glEnd();
	}

	glTranslatef(-p.getX(), -p.getY(), -p.getZ());

}
