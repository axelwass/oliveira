/*
 * UITextInput.h
 *
 *  Created on: Mar 24, 2011
 *      Author: mariano
 */

#include <string>
using namespace std;

#ifndef UITEXTINPUT_H_
#define UITEXTINPUT_H_

class UITextInput: public UITextLabel, public KeyListener {

	typedef UITextLabel super;

public:

	UITextInput(string text, int size, const Color& color, const Vector3& p) :
		UITextLabel(text, size, color, p) {
	}

	// should be key event ...
	virtual void onKeyDown(int key) {

		switch (key) {
		case '\b':
			if (text.size() > 0)
				text.erase(text.size() - 1);
			break;
		case '\n':
		case '\r':
			onAction();
			text = string("");
			break;
		default:
			text.append(1, key);
			break;
		}
		setString(text);
	}

	virtual void onKeyUp(int key) {

	}

	virtual void onAction() {
		printf("%s\n", text.c_str());
	}

};

#endif /* UITEXTINPUT_H_ */
