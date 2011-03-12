/*
 * MouseListener.h
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include "MouseManager.h"

#ifndef MOUSELISTENER_H_
#define MOUSELISTENER_H_

class MouseListener {
	public:
		MouseListener() {
			MouseManager::getInstance()->registerListener(this);
		}

		void registerListener() {
			MouseManager::getInstance()->registerListener(this);
		}

		// for now... just x,y
		virtual void onMouseMotion(int x, int y) = 0;
		virtual void onMouseRelativeMotion(int x, int y) = 0;

		virtual void onMouseWheelDown() = 0;
		virtual void onMouseWheelUp() = 0;

		virtual void onMouseLeftClickDown() = 0;
		virtual void onMouseLeftClickUp() = 0;

};

#endif /* MOUSELISTENER_H_ */
