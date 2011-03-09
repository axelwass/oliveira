/*
 * EngineMain.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include "../include/GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() {

	mainWindow = new MainWindow(1200, 600);

}

void GraphicsEngine::render() {

}

void GraphicsEngine::update() {
	mainWindow->Refresh(0);
}

