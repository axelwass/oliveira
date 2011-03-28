/*
 * RenderLayer.h
 *
 *  Created on: Mar 12, 2011
 *      Author: mmerchan
 */

#include "../Camera/Camera.h"
#include "Renderable.h"

#ifndef RENDERLAYER_H_
#define RENDERLAYER_H_

class RenderLayer {
protected:

	Camera * camera;

	// RenderGlobals * settings;
	list<Renderable *> objects;

public:
	RenderLayer() {
	}

	virtual void render() = 0;

	void addRenderable(Renderable * r) {
		this->objects.push_back(r);
	}

	Camera * getCamera() {
		return camera;
	}
};

#endif /* RENDERLAYER_H_ */
