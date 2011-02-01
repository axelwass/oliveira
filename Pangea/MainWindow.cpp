/*
 * MainWindow.cpp
 *
 *  Created on: Oct 19, 2009
 *      Author: Mariano
 */

#include "MainWindow.h"
#include <GL/glut.h>

/* Updates screen and also pops events */
int MainWindow::Refresh(int delay) {

	/* Update screen */
	glFlush();
	glFinish();
	SDL_GL_SwapBuffers();

	/* Pop an event, check for exit */
	SDL_PollEvent(&event);

	// Enable blending
	glEnable(GL_BLEND | GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// AA
	//	glEnable(GL_LINE_SMOOTH);
	//  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);


	//Enable textures
	//glEnable( GL_TEXTURE_2D );

	// Set background color
	glClearColor(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();

	// Set 2D view
	glViewport(0, 0, width, height);

	double ratio = 1.0 * width / height;
	gluPerspective(45, ratio, 1, 10000);
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(500, 1, 0, 0, 0, 0, 0, 1, 0);

	/* See if user presses ESC or quits */
	if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
			&& event.key.keysym.sym == SDLK_ESCAPE)) {
		SDL_FreeSurface(screen);
		SDL_Quit();
		return 0;
	} else
		return 1;
}

MainWindow::MainWindow(int width, int height) {
	this->width = width;
	this->height = height;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

	SDL_WM_SetCaption("Simple physics engine", NULL);

}

void MainWindow::End() {
	SDL_FreeSurface(screen);
	SDL_Quit();
}

MainWindow::~MainWindow() {
}

