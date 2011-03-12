/*
 * EngineMain.h
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include "Color.h"
#include "MainWindow.h"

#include "Camera/WalkthroughCamera.h"

#include "UserInterface/UIOverlay.h"

#include "UserInterface/UITextLabel.h"

#include "../../Events/Events.h"

#ifndef ENGINEMAIN_H_
#define ENGINEMAIN_H_

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

#endif /* ENGINEMAIN_H_ */
