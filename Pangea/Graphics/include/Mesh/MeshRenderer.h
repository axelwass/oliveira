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
#include "../Texture/Texture.h"

class AbstractMesh;

#ifndef MESHRENDERER_H_
#define MESHRENDERER_H_

class MeshRenderer: public Renderable {
protected:
	AbstractMesh * mesh;

	//for now texture, not material ... TODO
	Texture * texture;

public:
	MeshRenderer(AbstractMesh * mesh) :
		mesh(mesh) {
		texture = NULL;
	}

	void setTexture(Texture * t) {
		this->texture = t;
		this->texture->LoadTexture();
	}

	virtual void render() = 0;
};

#endif /* MESHRENDERER_H_ */
