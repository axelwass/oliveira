/*
 * EngineMain.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include "../include/GraphicsEngine.h"
#include <SDL/SDL.h>

GraphicsEngine::GraphicsEngine() {

	mainWindow = new MainWindow(1200, 600);

	mainCamera = new PerspectiveCamera(700, Vector3(), 35);

	observer = MouseManager::getInstance();
}

void GraphicsEngine::render() {
	mainCamera->render();
}

bool GraphicsEngine::update() {
	return mainWindow->Refresh(0);
}

