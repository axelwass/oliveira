/*
 * KeyListener.h
 *
 *  Created on: Mar 9, 2011
 *      Author: mmerchan
 */

#include "KeyManager.h"

#ifndef KEYLISTENER_H_
#define KEYLISTENER_H_


class KeyListener {
public:
	KeyListener(){
		KeyManager::getInstance()->registerListener(this);
	}

	// should be key event ...
	virtual void onKeyPress(int key) = 0;
};

#endif /* KEYLISTENER_H_ */
