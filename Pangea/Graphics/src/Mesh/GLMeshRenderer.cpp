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

void GLMeshRenderer::renderTransform(const Vector3& p, real size) {

	glDisable(GL_LIGHTING);

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, size);
	glEnd();

	glEnable(GL_LIGHTING);
}

void GLMeshRenderer::render() {

	Transform * t = mesh->getTransform();

	vector<Vertex *> vertices = *mesh->getVertices();
	vector<Vector3>& normals = mesh->getNormals();
	vector<Vector3>& txCoords = mesh->getTextureCoordinates();

	Vector3 s = t->getScale();
	Vector3 p = t->getPosition();
	Vector3 r = t->getRotation();
	real angle = r.magnitude() * 180.0 / 3.1415;

	r.normalize();

	renderTransform(p, 5);

	//      Sets color to red
	glTranslatef(p.getX(), p.getY(), p.getZ());
	glRotatef(angle, r.getX(), r.getY(), r.getZ());

	if (texture)
		texture->BindTexture();

	vector<Face *>::iterator faceItr = mesh->getFaces()->begin();
	for (; faceItr != mesh->getFaces()->end(); faceItr++) {

		vector<VertexWrapper>& faceVertices = (*faceItr)->getVertices();
		vector<VertexWrapper>::iterator vertexItr = faceVertices.begin();

		glBegin(wireframe ? GL_LINE_LOOP : GL_POLYGON);
		for (vertexItr = faceVertices.begin(); vertexItr != faceVertices.end(); vertexItr++) {
			int nIndex = (*vertexItr).getNormal();
			int pIndex = (*vertexItr).getVertex();
			int tIndex = (*vertexItr).getTexture();

			Vector3 normal, tx, pos;

			if (nIndex >= 0)
				normal = normals[nIndex];
			if (tIndex >= 0)
				tx = txCoords[tIndex];

			pos = vertices[pIndex]->getPosition();
			pos = pos.componentProduct(s);

			// Prevent normals from scaling!
			glNormal3f(normal.getX(), normal.getY(), normal.getZ());
			glTexCoord2f(tx.getX(), tx.getY());
			glVertex3f(pos.getX(), pos.getY(), pos.getZ());
		}
		glEnd();
	}

	if (texture)
		texture->UnbindTexture();

	glTranslatef(-p.getX(), -p.getY(), -p.getZ());
	glRotatef(-angle, r.getX(), r.getY(), r.getZ());

}
