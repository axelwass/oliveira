/*
 * ActionListener.h
 *
 *  Created on: Mar 26, 2011
 *      Author: mariano
 */

#include "ActionObserver.h"

/*
 * Very simple interface for basic action oriented events
 */

#ifndef ACTIONLISTENER_H_
#define ACTIONLISTENER_H_

class ActionListener {
public:
	ActionListener() {
	}

	virtual ~ActionListener() {
	}

	virtual void onAction() = 0;
};

#endif /* ACTIONLISTENER_H_ */
