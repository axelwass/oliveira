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

	int size = 256;

	MandelbrotTexture * m = new MandelbrotTexture(size, size, Vector3(), 2, 2);
	m->setColor(Color(255, 255, 255));
	UITexture * fractal = new UITexture(TexturePtr(m));
	fractal->setPosition(Vector3(0, 0, 0));
	ui->addUIComponent(fractal);

	/*
	 int size = 128;
	 int maxX = MainWindow::getInstance()->getWidth() / size;
	 int maxY = MainWindow::getInstance()->getHeight() / size;

	 for (int j = 0; j < maxY; j++)
	 for (int i = 0; i < maxX; i++) {

	 JuliaTexture * julia = new JuliaTexture(Vector3(), 2, 2, size,
	 size, 10, ((float) i) / maxX, (float) j / maxY);

	 julia->setColor(Color(rand() % 255, rand() % 255, rand() % 255));
	 UITexture * fractal = new UITexture(TexturePtr(julia));

	 fractal->setPosition(Vector3(size * i, size * j, 0));
	 ui->addUIComponent(fractal);

	 } */

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
	base3DLayer = objs;
	/*
	 MeshPlane * plane = new MeshPlane();

	 plane->getTransform()->setScale(Vector3(150, 150, 150));
	 plane->setRenderer(new GLMeshRenderer(plane));
	 objs->addRenderable(plane->getRenderer());

	 Mesh * m = MeshLoader::load("columna_2.obj");
	 m->getTransform()->setScale(Vector3(15, 15, 15));
	 m->setRenderer(new GLMeshRenderer(m));
	 m->getRenderer()->setTexture(new ImageTexture("test_tx.jpg"));
	 objs->addRenderable(m->getRenderer());
	 */
	// Order of 3d-ui is important until z-layers are implemented


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

