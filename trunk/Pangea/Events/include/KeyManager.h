/*
 * KeyManager.h
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include <list>
#include <SDL/SDL.h>
using namespace std;

class KeyListener;

#ifndef KEYMANAGER_H_
#define KEYMANAGER_H_

class KeyManager {
private:

	list<KeyListener *> listeners;

	static KeyManager * instance;

	KeyManager() {

	}

public:

	static KeyManager * getInstance() {
		if (instance == NULL)
			instance = new KeyManager();
		return instance;
	}

	void registerListener(KeyListener* l);

	void update(SDL_Event * event);

};

#endif /* KEYMANAGER_H_ */
