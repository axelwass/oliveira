/*
 * MouseObserver.cpp
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include "../include/MouseManager.h"
#include "../include/MouseListener.h"

#include <SDL/SDL.h>
#include <GL/glut.h>

MouseManager * MouseManager::instance = NULL;

void MouseManager::registerListener(MouseListener* l) {
	this->listeners.push_back(l);
}

void MouseManager::update(SDL_Event * event) {

	list<MouseListener*>::iterator elem;

	int relX, relY;

	switch (event->type) {
	case SDL_MOUSEMOTION:

		SDL_GetRelativeMouseState(&relX, &relY);

		for (elem = listeners.begin(); elem != listeners.end(); elem++) {
			(*elem)->onMouseMotion(event->button.x, event->button.y);
			(*elem)->onMouseRelativeMotion(relX, relY);
		}

		break;
	case SDL_MOUSEBUTTONDOWN:

		if (event->button.button == SDL_BUTTON_WHEELUP)
			for (elem = listeners.begin(); elem != listeners.end(); elem++)
				(*elem)->onMouseWheelUp();
		else if (event->button.button == SDL_BUTTON_WHEELDOWN)
			for (elem = listeners.begin(); elem != listeners.end(); elem++)
				(*elem)->onMouseWheelDown();
		else if (event->button.button == SDL_BUTTON_LEFT)
			for (elem = listeners.begin(); elem != listeners.end(); elem++)
				(*elem)->onMouseLeftClickDown();
		// either left middle or right button, or wheels
		break;
	case SDL_MOUSEBUTTONUP:
		if (event->button.button == SDL_BUTTON_LEFT)
			for (elem = listeners.begin(); elem != listeners.end(); elem++)
				(*elem)->onMouseLeftClickUp();
		break;
	default:
		break;
	}
}
