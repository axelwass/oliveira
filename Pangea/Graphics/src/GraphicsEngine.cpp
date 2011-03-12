/*
 * EngineMain.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include "../include/GraphicsEngine.h"
#include <SDL/SDL.h>

#include <sstream>
using namespace std;

GraphicsEngine::GraphicsEngine() {

	mainWindow = MainWindow::getInstance(1200, 600);

	UIOverlay * ui = new UIOverlay();
	ui->addUIComponent(new UITextLabel("Pangea Engine v0.01", 12, Color(150,
			150, 150), Vector3(2, 0, 0)));

	fpsCounter = new UITextLabel("Frames per second: ", 12,
			Color(150, 150, 150), Vector3(2, 15, 0));

	ui->addUIComponent(fpsCounter);

	layers.push_back(ui);

	mainCamera = new WalkthroughCamera(Vector3(-500, 0, 0), 5000, 1, 35);
}

void GraphicsEngine::render() {

	stringstream str;
	str << "Frames per second: " << MainWindow::getInstance()->getFPS();

	fpsCounter->setString(str.str());

	list<RenderLayer *>::iterator l;
	for (l = layers.begin(); l != layers.end(); l++)
		(*l)->render();

	mainCamera->render();
}

bool GraphicsEngine::update() {
	return mainWindow->Refresh(0);
}

