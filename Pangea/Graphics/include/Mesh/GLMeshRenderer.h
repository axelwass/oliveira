/*
 * OpenGLMeshRenderer.h
 *
 *  Created on: Aug 3, 2010
 *      Author: mmerchan
 */

#include "AbstractMesh.h"
#include "MeshRenderer.h"
#include "../Render/Renderable.h"

#include "../Texture/Texture.h"

#ifndef OPENGLMESHRENDERER_H_
#define OPENGLMESHRENDERER_H_

class GLMeshRenderer: public MeshRenderer {
protected:
	void renderTransform(const Vector3& p, real size);

	bool wireframe;

public:

	GLMeshRenderer(AbstractMesh * mesh, bool wireframe) :
		MeshRenderer(mesh) {
		this->wireframe = wireframe;
	}

	GLMeshRenderer(AbstractMesh * mesh) :
		MeshRenderer(mesh) {
		wireframe = false;
	}

	void render();
};

#endif /* OPENGLMESHRENDERER_H_ */
