/*
 * EngineMain.h
 *
 *  Created on: Jul 23, 2010
 *      Author: Mariano
 */

#include "MainWindow.h"

#ifndef ENGINEMAIN_H_
#define ENGINEMAIN_H_

class GraphicsEngine {

private:

	MainWindow * mainWindow;
	//Camera mainCamera;

public:
	GraphicsEngine();

	void render();

	void update();
};

#endif /* ENGINEMAIN_H_ */
