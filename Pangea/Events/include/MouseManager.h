/*
 * MouseObserver.h
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include <list>
#include <SDL/SDL.h>
using namespace std;

class MouseListener;

#ifndef MOUSEOBSERVER_H_
#define MOUSEOBSERVER_H_

class MouseManager {

private:

	list<MouseListener *> listeners;

	static MouseManager * instance;

	MouseManager() {
	}

public:

	static MouseManager * getInstance() {
		if (instance == NULL)
			instance = new MouseManager();
		return instance;
	}

	void registerListener(MouseListener* l);

	void update(SDL_Event * event);
};

#endif /* MOUSEOBSERVER_H_ */
