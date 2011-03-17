/*
 * MainWindow.cpp
 *
 *  Created on: Oct 19, 2009
 *      Author: Mariano
 */

#include "../include/MainWindow.h"
#include <GL/gl.h>
#include <SDL/SDL_ttf.h>

MainWindow * MainWindow::instance = NULL;

/* Updates screen and also pops events */
int MainWindow::Refresh(int delay) {

	real passedTime = SDL_GetTicks() - time;

	fps = 1000.0 / passedTime;

	time = SDL_GetTicks();

	/* Update screen */
	glFlush();
	glFinish();
	SDL_GL_SwapBuffers();

	// AA
	//	glEnable(GL_LINE_SMOOTH);
	//  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);


	// Set background color
	glClearColor(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set 2D view
	glViewport(0, 0, width, height);

	return running;
}

MainWindow::MainWindow(int width, int height) {
	this->width = width;
	this->height = height;
	this->running = true;

	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();

	SDL_EnableUNICODE(1);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

	SDL_WM_SetCaption("Pangea Engine", NULL);

	// Enable blending
	glEnable(GL_BLEND | GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable textures
	glEnable(GL_TEXTURE_2D);


	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	time = SDL_GetTicks();
}

void MainWindow::End() {
	SDL_FreeSurface(screen);
	SDL_Quit();
}

int MainWindow::getWidth() {
	return width;
}

int MainWindow::getHeight() {
	return height;
}

real MainWindow::getFPS() {
	return fps;
}

void MainWindow::onKeyUp(int key) {

}

void MainWindow::onKeyDown(int key) {
	if (key == 'q' || key == 27) {
		this->End();
		running = false;
	}
}

MainWindow::~MainWindow() {
}

