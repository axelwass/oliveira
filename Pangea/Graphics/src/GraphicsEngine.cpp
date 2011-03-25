#include "../include/GraphicsEngine.h"
#include <SDL/SDL.h>

#include <sstream>
using namespace std;

GraphicsEngine::GraphicsEngine() {

	mainWindow = MainWindow::getInstance(1200, 600);

	fpsCounter = NULL;

	UIOverlay * ui = new UIOverlay();

	// jajaja esto parece swing
	UITexture * logo = new UITexture(TexturePtr(new ImageTexture(
			"pangea_small.png")));
	logo->setPosition(Vector3(MainWindow::getInstance()->getWidth() - 80, 5, 0));
	ui->addUIComponent(logo);

	ui->addUIComponent(new UITextLabel("Engine v0.01", 12,
			Color(150, 150, 150), Vector3(2, 2, 0)));
	/*
	 UIWindow * window = new UIWindow(Vector3(10,
	 MainWindow::getInstance()->getHeight() - 160, 0), 400, 150, Color(
	 50, 50, 50, 100));

	 window->addUIComponent(new UITextInput("Enter command ...", 10, Color(255,
	 255, 255), Vector3(5, 130, 0)));



	 window->addUIComponent(new UITextLabel(":: Console window ::", 12, Color(
	 150, 150, 150), Vector3(2, 2, 0)));

	 ui->addUIComponent(window);
	 */
	fpsCounter = new UITextLabel("Frames per second: ", 12,
			Color(150, 150, 150), Vector3(2, 15, 0));
	ui->addUIComponent(fpsCounter);

	RenderLayer3D * objs = new RenderLayer3D();

	MeshPlane * plane = new MeshPlane();

	plane->getTransform()->setScale(Vector3(150, 150, 150));
	plane->setRenderer(new GLMeshRenderer(plane));
	objs->addRenderable(plane->getRenderer());
	/*
	 Mesh * m = MeshLoader::load("bunny.obj");
	 m->getTransform()->setScale(Vector3(150, 150, 15));
	 m->setRenderer(new GLMeshRenderer(m));
	 m->getRenderer()->setTexture(new ImageTexture("test_tx.jpg"));
	 objs->addRenderable(m->getRenderer());*/

	// Order of 3d-ui is important until z-layers are implemented


	layers.push_back(ui);

	layers.push_back(objs);

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

