/*
 * RenderLayer.cpp
 *
 *  Created on: Mar 12, 2011
 *      Author: mmerchan
 */

#include "../../include/Render/RenderLayer2D.h"
#include "../../include/Camera/OrthographicCamera.h"
#include "../../include/MainWindow.h"

#include <GL/gl.h>

RenderLayer2D::RenderLayer2D() {
	int w, h;
	w = MainWindow::getInstance()->getWidth();
	h = MainWindow::getInstance()->getHeight();
	this->camera = new OrthographicCamera(-1, 1, 0, w, h, 0);
}

void RenderLayer2D::render() {

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	this->camera->render();

}
