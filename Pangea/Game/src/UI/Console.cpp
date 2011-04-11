/*
 * Console.cpp
 *
 *  Created on: Apr 11, 2011
 *      Author: mariano
 */
#include "../../include/UI/Console.h"
#include "../../include/UI/ConsoleInput.h"

Console::Console(Vector3 position, int w, int h, Color bg) :
	UIWindow(position, w, h, bg) {

	row = 0;

	addUIComponent(new ConsoleInput(this, "Enter command here...", 12, bg * 5,
			Vector3(5, h - 20, 0)));
}

void Console::updateScreen(string text) {

	UITextLabel * label = new UITextLabel(text, 10, Color(255, 255, 255),
			Vector3(5, row, 0));
	rows.push_back(label);
	this ->addUIComponent(label);

	if (row + 15 > height - 20) {

		list<UITextLabel *>::iterator itr;
		for (itr = rows.begin(); itr != rows.end(); itr++) {

			(*itr)->translate(Vector3(0, -15, 0));
		}

	} else
		row += 15;
}
