/*
 * MainWindow.h
 *
 *  Created on: Oct 19, 2009
 *      Author: Mariano
 */
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "../../Events/Events.h"
#include "../../Generic/Generic.h"

#include <SDL/SDL.h>

class MainWindow: public KeyListener {

	private:

		SDL_Surface * screen;
		int width, height;
		bool running;

		real fps;
		real time;

		static MainWindow * instance;

		MainWindow(int width, int height);

	public:

		static MainWindow * getInstance() {
			return instance;
		}

		static MainWindow * getInstance(int width, int height) {
			if (instance == NULL)
				instance = new MainWindow(width, height);
			return instance;
		}

		SDL_Event event;
		int Refresh(int delay);

		virtual ~MainWindow();
		void End();

		void onKeyDown(int key);
		void onKeyUp(int key);

		int getWidth();
		int getHeight();
		real getFPS();
};

#endif /* MAINWINDOW_H_ */
