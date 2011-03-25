/*
 * ParticleWorld.cpp
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#include "../../include/world/ParticleWorld.h"
#include "../../include/emitter/Emitter.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

//#include <GL/glew.h>

ParticleWorld::ParticleWorld(real precision) {
	this->precision = precision;
	this->time = 0.0;

	// threshold more than 2 to prevent possible infinite partition due to equal vectors
	groupsOctree = OctreePtr(
			new Octree<ParticleGroup> (Vector3(), 2, 100, true));
}

/*
 * The main function of the engine
 */
void ParticleWorld::runPhysics() {
	particleEmission();
	integrate();
	time += precision;
}

void ParticleWorld::particleEmission() {
	list<Emitter *>::iterator e = emitters.begin();

	for (; e != emitters.end(); e++)
		(*e)->emit();
}

void ParticleWorld::addEmitter(Emitter * emitter) {
	this->emitters.push_back(emitter);
}

void ParticleWorld::addParticleGroup(ParticleGroupPtr group) {
	this->groups.push_back(group);
	if (!this->groupsOctree->put(group.get()))
		printf("Group octree failed\n");
}

void ParticleWorld::removeParticleGroup(ParticleGroupPtr group) {
	this->groups.remove(group);
	this->groupsOctree->remove(group.get());
}

void ParticleWorld::resolveGroupCollisions() {
	list<ParticleGroupPtr>::iterator g;
	for (g = groups.begin(); g != groups.end(); g++) {

		ShapePtr shape = (*g)->getCollisionShape();

		list<Positionable<ParticleGroup> *> closestGroups =
				groupsOctree->getIntersectionElements(shape.get());

		list<Positionable<ParticleGroup> *>::iterator closeGroup;
		for (closeGroup = closestGroups.begin(); closeGroup
				!= closestGroups.end(); closeGroup++) {
			ParticleGroup * other = (*closeGroup)->getThis();

			if (other != (*g).get()) {
				IntersectionData data = (*g)->checkCollision(*other);

				if (data.hasIntersected())
					(*g)->resolveCollision(*other, data);
			}
		}
	}
}

/*
 * Integrates each group, synchronizing each step.
 *
 * TODO: Convertir esto en  n~#particulas threads, sincronizados con un monitor
 */
void ParticleWorld::integrate() {
	list<ParticleGroupPtr>::iterator itr;

	// Finishes when every particle finishes (they all have the same step)
	for (int i = 0; i < 4; i++) {

		groupsOctree->update();
		resolveGroupCollisions();
		// Integrate groups synchronized
		for (itr = groups.begin(); itr != groups.end(); itr++)
			(*itr)->integrateStep(time, precision);

		// Apply step
		for (itr = groups.begin(); itr != groups.end(); itr++)
			(*itr)->applyStep(precision);
	}
}

// PARA TESTEAR!!!
void ParticleWorld::render() {

	//	groupsOctree->render(NULL, false);

	// Draw Particles
	list<ParticleGroupPtr>::iterator group;
	for (group = groups.begin(); group != groups.end(); group++)
		(*group)->render();

}

real ParticleWorld::getTime() {
	return time;
}
