/*
 * EventsManager.h
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include "MouseManager.h"
#include "KeyManager.h"
#include "MouseEvent.h"
#include <SDL/SDL.h>

#ifndef EVENTSMANAGER_H_
#define EVENTSMANAGER_H_

class EventsManager {
private:
	MouseManager * mouseManager;
	KeyManager * keyManager;

public:
	EventsManager() {
		mouseManager = MouseManager::getInstance();
		keyManager = KeyManager::getInstance();
	}

	void update() {
		updateSDL();
	}

	// This should be a derived class!
	void updateSDL() {

		SDL_Event event;

		MouseEventType mouseType;

		while (SDL_PollEvent(&event))
			switch (event.type) {
			case SDL_MOUSEMOTION:
				mouseType = MOUSE_MOTION;
				sendMouseEvent(mouseType, event);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseType = MOUSE_BUTTON_DOWN;
				sendMouseEvent(mouseType, event);
				break;
			case SDL_MOUSEBUTTONUP:
				mouseType = MOUSE_BUTTON_UP;
				sendMouseEvent(mouseType, event);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				keyManager->update(&event);
				break;
			default:
				break;
			}

	}

	// Basically construct an implementation independent event and send it to mouse manager
	void sendMouseEvent(MouseEventType type, SDL_Event& event) {

		int x, y, relX, relY;
		MouseEventButton button;

		x = event.button.x;
		y = event.button.y;

		switch (event.button.button) {
		case SDL_BUTTON_WHEELUP:
			button = MOUSE_WHEEL_UP;
			break;
		case SDL_BUTTON_WHEELDOWN:
			button = MOUSE_WHEEL_DOWN;
			break;
		case SDL_BUTTON_LEFT:
			button = MOUSE_BUTTON_LEFT;
			break;
		case SDL_BUTTON_RIGHT:
			button = MOUSE_BUTTON_RIGHT;
			break;
		case SDL_BUTTON_MIDDLE:
			button = MOUSE_BUTTON_MIDDLE;
			break;
		}

		SDL_GetRelativeMouseState(&relX, &relY);

		MouseEvent mouseEvent(x, y, relX, relY, type, button);
		mouseManager->update(mouseEvent);
	}
};

#endif /* EVENTSMANAGER_H_ */
