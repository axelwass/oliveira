/*
 * CollisionEvent.h
 *
 *  Created on: Apr 14, 2011
 *      Author: mmerchan
 */

#include <tr1/memory>

class Particle;

class CollisionEvent;

typedef std::tr1::shared_ptr<CollisionEvent> CollisionEventPtr;

#ifndef COLLISIONEVENT_H_
#define COLLISIONEVENT_H_

class CollisionEvent {

public:

	// Lost magnitudes due to speculation
	real v1, v2;
	Particle * p1, *p2;

	CollisionEvent(Particle * p1, real v2, Particle * p2, real v2);
	virtual ~CollisionEvent();
	bool operator==(const CollisionEvent& e);

};

#endif /* COLLISIONEVENT_H_ */
