/*
 * MouseListener.h
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include "MouseManager.h"
#include "MouseEvent.h"

#ifndef MOUSELISTENER_H_
#define MOUSELISTENER_H_

class MouseListener {
public:
	MouseListener() {
		MouseManager::getInstance()->registerListener(this);
	}

	virtual void onMouseMotion(MouseEvent event) = 0;

	virtual void onMouseWheelDown(MouseEvent event) = 0;
	virtual void onMouseWheelUp(MouseEvent event) = 0;

	virtual void onMouseLeftClickDown(MouseEvent event) = 0;
	virtual void onMouseLeftClickUp(MouseEvent event) = 0;

	virtual void onMouseLeftClick(MouseEvent event) = 0;

};

#endif /* MOUSELISTENER_H_ */
