/*
 * ActionObserver.h
 *
 *  Created on: Mar 26, 2011
 *      Author: mariano
 */

#include <list>
#include <tr1/memory>
using namespace std;

class ActionListener;

typedef tr1::shared_ptr<ActionListener> ActionListenerPtr;

#ifndef ACTIONOBSERVER_H_
#define ACTIONOBSERVER_H_

class ActionObserver {
protected:

	list<ActionListenerPtr> listeners;

public:
	ActionObserver();

	virtual ~ActionObserver();

	void registerListener(ActionListenerPtr l);

	void triggerActionEvent();
};

#endif /* ACTIONOBSERVER_H_ */
