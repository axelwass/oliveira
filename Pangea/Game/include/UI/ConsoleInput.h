/*
 * ConsoleInput.h
 *
 *  Created on: Apr 11, 2011
 *      Author: mariano
 */

#include "../../Game.h"
#include "Console.h"

#ifndef CONSOLEINPUT_H_
#define CONSOLEINPUT_H_

class ConsoleInput: public UITextInput {
private:
	Console * console;

	typedef UITextInput super;
public:
	ConsoleInput(Console * c, string text, int size, const Color& color,
			const Vector3& p) :
		UITextInput(text, size, color, p) {
		this->console = c;
	}

	virtual void onKeyDown(int key) {

		if (text == "Enter command here...") {
			text = "";
		}

		super::onKeyDown(key);

	}

	virtual void onAction() {
		console->updateScreen(text);
	}

};

#endif /* CONSOLEINPUT_H_ */
