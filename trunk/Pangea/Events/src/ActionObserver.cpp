/*
 * ActionObserver.cpp
 *
 *  Created on: Mar 26, 2011
 *      Author: mariano
 */

#include "../include/ActionObserver.h"
#include "../include/ActionListener.h"

ActionObserver::ActionObserver() {
}

ActionObserver::~ActionObserver() {
}

void ActionObserver::registerListener(ActionListenerPtr l) {
	listeners.push_back(l);
}

void ActionObserver::triggerActionEvent() {
	list<ActionListenerPtr>::iterator l;
	for (l = listeners.begin(); l != listeners.end(); l++)
		(*l)->onAction();
}
