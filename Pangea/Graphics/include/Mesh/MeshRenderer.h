/*
 * MeshRenderer.h
 *
 *  Created on: Aug 3, 2010
 *      Author: mmerchan
 */

/**
 * Just an interface for Mesh rendering.
 */

#include "../Render/Renderable.h"

class AbstractMesh;

#ifndef MESHRENDERER_H_
#define MESHRENDERER_H_

class MeshRenderer : public Renderable {
	protected:
		AbstractMesh * mesh;
	public:
		MeshRenderer(AbstractMesh * mesh) :
			mesh(mesh) {
		}

		virtual void render() = 0;
};

#endif /* MESHRENDERER_H_ */
