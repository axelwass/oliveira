/*
 * CollisionEvent.cpp
 *
 *  Created on: Apr 14, 2011
 *      Author: mmerchan
 */

#include "../../include/collision/CollisionEvent.h"
#include <stdio.h>

CollisionEvent::CollisionEvent(Particle * p1, Particle * p2) {
	this->p1 = p1;
	this->p2 = p2;
}

CollisionEvent::~CollisionEvent() {
}

bool CollisionEvent::operator==(const CollisionEvent& e) {
	return (p1 == e.p1 && p2 == e.p2) || (p1 == e.p2 && p2 == e.p1);
}
