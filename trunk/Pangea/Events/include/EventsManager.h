/*
 * EventsManager.h
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include "MouseManager.h"
#include "KeyManager.h"
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
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			mouseManager->update(&event);
			keyManager->update(&event);
		}
	}
};

#endif /* EVENTSMANAGER_H_ */
