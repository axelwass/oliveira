#include "../include/GraphicsEngine.h"
#include <SDL/SDL.h>

#include <sstream>
using namespace std;

GraphicsEngine::GraphicsEngine() {

	mainWindow = MainWindow::getInstance(1200, 600);

	fpsCounter = NULL;

	UIOverlay * ui = new UIOverlay();

	// jajaja esto parece swing
	UITexture * logo = new UITexture(new ImageTexture("pangea_small.png"));
	logo->setPosition(Vector3(MainWindow::getInstance()->getWidth() - 80, 5, 0));
	ui->addUIComponent(logo);

	ui->addUIComponent(new UITextLabel("Pangea Engine v0.01", 12, Color(150,
			150, 150), Vector3(2, 2, 0)));

	fpsCounter = new UITextLabel("Frames per second: ", 12,
			Color(150, 150, 150), Vector3(2, 15, 0));
	ui->addUIComponent(fpsCounter);

	RenderLayer3D * objs = new RenderLayer3D();

	Mesh * m = MeshLoader::load("bunny.obj");
	m->setScale(Vector3(1000, 1000, 1000));
	m->setRenderer(new GLMeshRenderer(m));
	//objs->addRenderable(m->getRenderer());

	layers.push_back(objs);
	layers.push_back(ui);
}

void GraphicsEngine::render() {

	//test eh!
	if (fpsCounter != NULL) {
		stringstream str;
		str << "Frames per second: " << MainWindow::getInstance()->getFPS();
		fpsCounter->setString(str.str());
	}

	list<RenderLayer *>::iterator l;
	for (l = layers.begin(); l != layers.end(); l++)
		(*l)->render();
}

bool GraphicsEngine::update() {
	return mainWindow->Refresh(0);
}

