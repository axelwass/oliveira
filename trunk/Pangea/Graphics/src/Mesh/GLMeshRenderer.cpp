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
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(p.getX(), p.getY(), p.getZ());

	glScalef(s.getX(), s.getY(), s.getZ());

	list<Face *>::iterator faceItr = mesh->getFaces()->begin();
	for (; faceItr != mesh->getFaces()->end(); faceItr++) {

		list<Vertex *> faceVertices = (*faceItr)->getVertices();
		list<Vertex *>::iterator vertexItr = faceVertices.begin();
		glBegin(GL_POLYGON);

		for (; vertexItr != faceVertices.end(); vertexItr++) {
			Vector3 normal = (*faceItr)->getNormal();

			glNormal3f(normal.getX(), normal.getZ(), normal.getY());

			glVertex3f((*vertexItr)->getPosition().getX(),
					(*vertexItr)->getPosition().getZ(),
					(*vertexItr)->getPosition().getY());

		}
		glEnd();

	}

	glTranslatef(-p.getX(), -p.getY(), -p.getZ());

}
