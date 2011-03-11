/*
 * EngineMain.h
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include "Color.h"
#include "Texture.h"
#include "ImageTexture.h"
#include "TextTexture.h"
#include "MainWindow.h"
#include "Camera/PerspectiveCamera.h"
#include "Camera/Camera.h"
#include "../../Events/Events.h"

#ifndef ENGINEMAIN_H_
#define ENGINEMAIN_H_

class GraphicsEngine {

private:

	MainWindow * mainWindow;
	Camera *  mainCamera;

	MouseManager * observer;

public:
	GraphicsEngine();

	void render();

	bool update();
};

#endif /* ENGINEMAIN_H_ */