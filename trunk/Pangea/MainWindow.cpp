/*
 * MainWindow.cpp
 *
 *  Created on: Oct 19, 2009
 *      Author: Mariano
 */

#include "MainWindow.h"

/* Updates screen and also pops events */
int MainWindow::Refresh(int delay){

	/* Update screen */
	glFlush();
	glFinish();
	SDL_GL_SwapBuffers();

	/* Pop an event, check for exit */
	SDL_PollEvent( &event );

	// Enable blending
	glEnable (GL_BLEND | GL_ALPHA_TEST);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// AA
//	glEnable(GL_LINE_SMOOTH);
  //  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);


	//Enable textures
	glEnable( GL_TEXTURE_2D );

	// Set background color
	glClearColor( 35/255.0f, 35/255.0f, 35/255.0f, 1 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Set 2D view (orthographic)
	glViewport( 0,0, width,height );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(-width/2,width/2,height/2,-height/2,-500.0f, 500.0f);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

    //gluLookAt (width/2, height/2, -870, width/2, height/2, 0.0, 0.0,-1.0, 0.0); //set the view

	/* See if user presses ESC or quits */
	if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
	   event.key.keysym.sym == SDLK_ESCAPE)){
			SDL_FreeSurface(screen);
			SDL_Quit();
		return 0;
	} else return 1;
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

	SDL_WM_SetCaption("Simple 3D engine", NULL);

}

void MainWindow::End() {
	SDL_FreeSurface(screen);
	SDL_Quit();
}

MainWindow::~MainWindow() {
}

