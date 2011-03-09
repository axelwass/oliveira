/*
 * MouseObserver.cpp
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include "../include/MouseManager.h"
#include "../include/MouseListener.h"

#include <SDL/SDL.h>

MouseManager * MouseManager::instance = NULL;

void MouseManager::registerListener(MouseListener* l) {
	this->listeners.push_back(l);
}

void MouseManager::update(SDL_Event * event) {

	list<MouseListener*>::iterator elem;

	switch (event->type) {
	case SDL_MOUSEMOTION:
		for (elem = listeners.begin(); elem != listeners.end(); elem++)
			(*elem)->onMouseMotion(event->button.x, event->button.y);
		break;
	case SDL_MOUSEBUTTONDOWN:

		if (event->button.button == SDL_BUTTON_WHEELUP)
			for (elem = listeners.begin(); elem != listeners.end(); elem++)
				(*elem)->onMouseWheelUp();
		else if (event->button.button == SDL_BUTTON_WHEELDOWN)
			for (elem = listeners.begin(); elem != listeners.end(); elem++)
				(*elem)->onMouseWheelDown();

		// either left middle or right button, or wheels
		break;
	case SDL_MOUSEBUTTONUP:
		// either left middle or right button, or wheels
		break;
	default:
		break;
	}
}
