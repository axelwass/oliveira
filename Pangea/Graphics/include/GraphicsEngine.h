#include "Color.h"
#include "MainWindow.h"

#include "Camera/WalkthroughCamera.h"

#include "Mesh/Mesh.h"
#include "Mesh/Primitives/MeshPlane.h"
#include "Mesh/MeshRenderer.h"
#include "Mesh/GLMeshRenderer.h"
#include "Mesh/MeshLoader.h"

#include "Texture/ImageTexture.h"

#include "Render/RenderLayer3D.h"
#include "Render/RenderLayer2D.h"

#include "UserInterface/UIOverlay.h"
#include "UserInterface/UIWindow.h"
#include "UserInterface/UITextLabel.h"
#include "UserInterface/UITextInput.h"
#include "UserInterface/UITexture.h"

#include "../../Events/Events.h"

#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

class GraphicsEngine {

private:

	MainWindow * mainWindow;
	Camera * mainCamera;

	list<RenderLayer *> layers;

	// FEISIMO ESTO jajaja
	UITextLabel * fpsCounter;

public:
	GraphicsEngine();

	void render();

	bool update();
};

#endif /* GRAPHICSENGINE_H_ */
