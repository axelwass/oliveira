/*
 * main.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "Physics/Physics.h"
#include "Graphics/Graphics.h"
#include "Events/Events.h"

#include <GL/glut.h>

// LEER todo.txt

int main(int argc, char *argv[]) {

	srand(time(NULL));

	// initialize glut!
	glutInit(&argc, (char**) argv);

	GraphicsEngine gEngine;
	EventsManager events;

	while (gEngine.update()) {
		events.update();
		gEngine.render();

	}

	return 0;
}
