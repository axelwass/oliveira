/*
 * RenderLayer3D.cpp
 *
 *  Created on: Mar 14, 2011
 *      Author: mmerchan
 */

#include "../../include/Render/RenderLayer3D.h"
#include "../../include/Camera/WalkthroughCamera.h"
#include "../../include/MainWindow.h"

#include "../../include/Color.h"

RenderLayer3D::RenderLayer3D() {

	// por ahora asi..
	this->camera = new WalkthroughCamera(Vector3(-500, 0, 0), 5000, 1, 35);

}

void RenderLayer3D::render() {

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	this->camera->render();

	list<Renderable *>::iterator o;
	for (o = objects.begin(); o != objects.end(); o++)
		(*o)->render();

}
