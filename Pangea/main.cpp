/*
 * main.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "Game/Game.h"

#include <GL/glut.h>

// LEER todo.txt
int main(int argc, char *argv[]) {

	// initialize glut!
	glutInit(&argc, (char**) argv);

	GameEngine();
	return 0;
}
