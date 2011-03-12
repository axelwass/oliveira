/*
 * RenderLayer.h
 *
 *  Created on: Mar 12, 2011
 *      Author: mmerchan
 */

#include "../Camera/Camera.h"

#ifndef RENDERLAYER_H_
#define RENDERLAYER_H_

class RenderLayer {
	protected:

		Camera * camera;

		// RenderGlobals * settings;
		// list<Renderable *> objects;

	public:
		RenderLayer() {
		}

		virtual void render() = 0;
};

#endif /* RENDERLAYER_H_ */
