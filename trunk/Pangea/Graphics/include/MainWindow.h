/*
 * MainWindow.h
 *
 *  Created on: Oct 19, 2009
 *      Author: Mariano
 */
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "../../Events/Events.h"

#include <SDL/SDL.h>

class MainWindow: public KeyListener {

private:

	SDL_Surface * screen;
	int width, height;

	bool running;

public:

	SDL_Event event;
	int Refresh(int delay);
	MainWindow(int width, int height);
	virtual ~MainWindow();
	void End();

	void onKeyPress(int key);
};

#endif /* MAINWINDOW_H_ */
