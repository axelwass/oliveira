/*
 * MouseObserver.h
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include <list>
#include "MouseEvent.h"
using namespace std;

class MouseListener;

#ifndef MOUSEOBSERVER_H_
#define MOUSEOBSERVER_H_

class MouseManager {

private:

	list<MouseListener *> listeners;
	static MouseManager * instance;

	bool leftPress, rightPress;

	MouseManager() {
		leftPress = false;
		rightPress = false;
	}

public:

	static MouseManager * getInstance() {
		if (instance == NULL)
			instance = new MouseManager();
		return instance;
	}

	void registerListener(MouseListener* l);

	void update(MouseEvent event);
};

#endif /* MOUSEOBSERVER_H_ */
