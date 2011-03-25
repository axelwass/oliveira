/*
 * MouseEvent.cpp
 *
 *  Created on: Mar 24, 2011
 *      Author: mariano
 */

#include "../include/MouseEvent.h"

int MouseEvent::getX() {
	return x;
}

int MouseEvent::getY() {
	return y;
}

int MouseEvent::getRelativeX() {
	return relX;
}

int MouseEvent::getRelativeY() {
	return relY;
}

MouseEventType MouseEvent::getType() {
	return type;
}

MouseEventButton MouseEvent::getButton() {
	return button;
}
