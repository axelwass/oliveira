/*
 * MouseEvent.h
 *
 *  Created on: Mar 24, 2011
 *      Author: mariano
 */

#ifndef MOUSEEVENT_H_
#define MOUSEEVENT_H_

typedef enum {
	MOUSE_BUTTON_DOWN, MOUSE_BUTTON_UP, MOUSE_MOTION
} MouseEventType;

typedef enum {
	MOUSE_WHEEL_UP,
	MOUSE_WHEEL_DOWN,
	MOUSE_BUTTON_RIGHT,
	MOUSE_BUTTON_LEFT,
	MOUSE_BUTTON_MIDDLE
} MouseEventButton;

class MouseEvent {

private:

	MouseEventButton button;
	MouseEventType type;

	int x, y;
	int relX, relY;

public:
	MouseEvent(int x, int y, int relX, int relY, MouseEventType type,
			MouseEventButton button) :
		x(x), y(y), relX(relX), relY(relY), type(type), button(button) {
	}

	int getX();
	int getY();
	int getRelativeX();
	int getRelativeY();

	MouseEventType getType();

	MouseEventButton getButton();
};

#endif /* MOUSEEVENT_H_ */
