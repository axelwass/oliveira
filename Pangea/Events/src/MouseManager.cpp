/*
 * MouseObserver.cpp
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include "../include/MouseManager.h"
#include "../include/MouseListener.h"

MouseManager * MouseManager::instance = NULL;

void MouseManager::registerListener(MouseListener* l) {
	this->listeners.push_back(l);
}

void MouseManager::update(MouseEvent event) {

	list<MouseListener*>::iterator elem;

	MouseEventButton button = event.getButton();

	switch (event.getType()) {
	case MOUSE_MOTION:
		for (elem = listeners.begin(); elem != listeners.end(); elem++)
			(*elem)->onMouseMotion(event);
		break;
	case MOUSE_BUTTON_DOWN:
		if (button == MOUSE_WHEEL_UP)
			for (elem = listeners.begin(); elem != listeners.end(); elem++)
				(*elem)->onMouseWheelUp(event);
		else if (button == MOUSE_WHEEL_DOWN)
			for (elem = listeners.begin(); elem != listeners.end(); elem++)
				(*elem)->onMouseWheelDown(event);
		else if (button == MOUSE_BUTTON_LEFT) {
			leftPress = true;
			for (elem = listeners.begin(); elem != listeners.end(); elem++)
				(*elem)->onMouseLeftClickDown(event);
		}
		// either left middle or right button, or wheels
		break;
	case MOUSE_BUTTON_UP:
		if (button == MOUSE_BUTTON_LEFT) {
			for (elem = listeners.begin(); elem != listeners.end(); elem++)
				(*elem)->onMouseLeftClickUp(event);
			if (leftPress) {
				leftPress = false;
				for (elem = listeners.begin(); elem != listeners.end(); elem++)
					(*elem)->onMouseLeftClick(event);
			}
		}
		break;
	default:
		break;
	}
}
