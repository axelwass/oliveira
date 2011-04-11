/*
 * Console.h
 *
 *  Created on: Apr 11, 2011
 *      Author: mariano
 */

#include "../../Game.h"

#ifndef CONSOLE_H_
#define CONSOLE_H_

class Console: public UIWindow {
private:
	int row;
	list<UITextLabel *> rows;
public:
	Console(Vector3 position, int w, int h, Color bg);

	void updateScreen(string text);
};

#endif /* CONSOLE_H_ */
