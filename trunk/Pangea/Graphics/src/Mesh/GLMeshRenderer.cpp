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

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, size);
	glEnd();
}

void GLMeshRenderer::render() {

	Transform * t = mesh->getTransform();

	vector<Vertex *> vertices = *mesh->getVertices();
	vector<Vector3>& normals = mesh->getNormals();
	vector<Vector3>& txCoords = mesh->getTextureCoordinates();

	Vector3 s = t->getScale();
	Vector3 p = t->getPosition().componentProduct(s);

	renderTransform(p, 5);

	//      Sets color to red
	glTranslatef(p.getX(), p.getY(), p.getZ());

	if (texture)
		texture->BindTexture();

	vector<Face *>::iterator faceItr = mesh->getFaces()->begin();
	for (; faceItr != mesh->getFaces()->end(); faceItr++) {

		vector<VertexWrapper>& faceVertices = (*faceItr)->getVertices();
		vector<VertexWrapper>::iterator vertexItr = faceVertices.begin();

		Vector3 normal;
		Vector3 vPos;

		glBegin(GL_POLYGON);
		for (vertexItr = faceVertices.begin(); vertexItr != faceVertices.end(); vertexItr++) {
			int nIndex = (*vertexItr).getNormal();
			int pIndex = (*vertexItr).getVertex();
			int tIndex = (*vertexItr).getTexture();

			Vector3 normal, tx, pos;

			if ((*faceItr)->hasVertexNormals())
				normal = normals[nIndex];
			if ((*faceItr)->isTexturizable())
				tx = txCoords[tIndex];
			pos = vertices[pIndex]->getPosition();
			vPos = pos.componentProduct(s);

			// Prevent normals from scaling!

			glNormal3f(normal.getX(), normal.getY(), normal.getZ());
			glTexCoord2f(tx.getX(), tx.getY());
			glVertex3f(vPos.getX(), vPos.getY(), vPos.getZ());
		}
		glEnd();
	}

	if (texture)
		texture->UnbindTexture();

	glTranslatef(-p.getX(), -p.getY(), -p.getZ());

}
