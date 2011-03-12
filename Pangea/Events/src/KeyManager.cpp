/*
 * KeyManager.cpp
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include "../include/KeyManager.h"
#include "../include/KeyListener.h"

KeyManager * KeyManager::instance = NULL;

void KeyManager::registerListener(KeyListener* l) {
	this->listeners.push_back(l);
}

void KeyManager::update(SDL_Event * event) {

	list<KeyListener*>::iterator elem;

	switch (event->type) {
	case SDL_KEYDOWN:
		for (elem = listeners.begin(); elem != listeners.end(); elem++)
			(*elem)->onKeyDown(event->key.keysym.sym);
		break;
	case SDL_KEYUP:
		for (elem = listeners.begin(); elem != listeners.end(); elem++)
			(*elem)->onKeyUp(event->key.keysym.sym);
		break;
	default:
		break;
	}

	// Aca va un typed, que es una combinacion de down+up
}
