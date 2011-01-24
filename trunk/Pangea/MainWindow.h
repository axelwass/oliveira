/*
 * MainWindow.h
 *
 *  Created on: Oct 19, 2009
 *      Author: Mariano
 */
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <SDL/SDL.h>
#include <GL/glew.h>
//#include <GL/glew.h>


class MainWindow {

	private:

		SDL_Surface * screen;
		int width, height;

	public:

		SDL_Event event;
		int Refresh(int delay);
		MainWindow(int width, int height);
		virtual ~MainWindow();
		void End();
};

#endif /* MAINWINDOW_H_ */
