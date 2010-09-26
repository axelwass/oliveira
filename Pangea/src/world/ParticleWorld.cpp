/*
 * ParticleWorld.cpp
 *
 *  Created on: 25/09/2010
 *      Author: Mariano
 */

#include "../../include/world/ParticleWorld.h"
#include <iostream>
#include <GL/GL.h>

ParticleWorld::ParticleWorld(real precision) {
	this->precision = precision;
	this->time = 0.0;
}

/*
 * The main function of the engine
 */
void ParticleWorld::runPhysics() {
	updateForces();
	integrate();
	time += precision;
}

/*
 * Add a particle to the world
 */
void ParticleWorld::addParticle(real inverseMass, const Vector3& pos,
		const Vector3& velocity) {
	ParticleData data(pos, inverseMass);
	data.setVelocity(velocity);
	this->particles.push_back(new Particle(data));
}

/*
 * Add a general force affecting all particles
 */
void ParticleWorld::addWorldInteraction(Force * force) {
	list<Particle *>::iterator itr;
	for (itr = particles.begin(); itr != particles.end(); itr++)
		this->interactions.push_back(new ParticleInteraction((*itr),
				&this->worldParticle, force));
}

/*
 * Basically create inter particle forces, such as elastic forces, gravitation, etc.
 */
void ParticleWorld::addPerParticleInteraction(InterParticleForce * force) {
	list<Particle *>::iterator itr;
	list<Particle *>::iterator itr2;
	for (itr = particles.begin(); itr != particles.end(); itr++)
		for (itr2 = particles.begin(); itr2 != particles.end(); itr2++)
			if ((*itr) != (*itr2)) {
				InterParticleForce * f = force->getFunctionCopy();
				f->setParticleData(*itr2);
				this->interactions.push_back(new ParticleInteraction((*itr),
						(*itr2), f));
			}
}

/*
 * Updates the force accumulators on each particle
 */
void ParticleWorld::updateForces() {
	list<ParticleInteraction *>::iterator itr;
	for (itr = interactions.begin(); itr != interactions.end(); itr++)
		(*itr)->resolve();
}

/*
 * Integrates each particle, synchronizing each step.
 */
void ParticleWorld::integrate() {
	list<Particle *>::iterator itr;
	bool integrating = true;

	// Finishes when every particle finishes (they all have the same step)
	while (integrating) {
		integrating = particles.empty() ? false : true;
		for (itr = particles.begin(); itr != particles.end(); itr++)
			integrating = !((*itr)->integrate(time, precision)) && integrating;
	}
}

void ParticleWorld::resolveCollisions() {
	//TODO
}

// PARA TESTEAR!!!
void ParticleWorld::render() {
	// Draw Particles
	list<Particle *>::iterator i;

	glColor3f(1.0, 1.0, 1.0);
	for (i = particles.begin(); i != particles.end(); i++) {

		glLineWidth(1);
		glBegin(GL_POLYGON);

		for (double angle = 0; angle < 2 * 3.14; angle += 0.2)
			glVertex3f((*i)->getData().getPosition().getX() + cos(angle)
					* (*i)->getData().getMass(),
					(*i)->getData().getPosition().getY() + sin(angle)
							* (*i)->getData().getMass(),
					(*i)->getData().getPosition().getZ());

		glEnd();

	}
}
