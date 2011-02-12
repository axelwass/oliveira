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
#include <GL/glew.h>

//#include <GL/glew.h>

ParticleWorld::ParticleWorld(real precision) {
	this->precision = precision;
	this->time = 0.0;
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

/*
 * Add a particle to the world
 */
Particle * ParticleWorld::addParticle(real inverseMass, const Vector3& pos,
		const Vector3& velocity) {
	ParticleData data(pos, inverseMass);
	data.setVelocity(velocity);
	Particle * p = new Particle(data);

	list<Force *>::iterator itr;
	for (itr = fields.begin(); itr != fields.end(); itr++)
		p->addForce((*itr));

	this->particles.push_back(p);

	return p;
}

void ParticleWorld::addParticleInteraction(Particle * p1, Particle * p2,
		Force * f) {
	ParticleInteraction * i = new ParticleInteraction(p1, p2, f);
	this->interactions.push_back(i);
}

Particle * ParticleWorld::addInternalSpring(const Vector3& v1,
		const Vector3& v2, real inverseMass, real k, real l) {

	Particle * p1 = new Particle(v1, inverseMass);
	Particle * p2 = new Particle(v2, inverseMass);

	this->particles.push_back(p1);
	this->particles.push_back(p2);

	this->interactions.push_back(new ParticleInteraction(p1, p2,
			new SpringForce(k, l, p2)));
	this->interactions.push_back(new ParticleInteraction(p2, p1,
			new SpringForce(k, l, p1)));

	return p2;
}

/*
 * Add a springe
 */
void ParticleWorld::addSpring(const Vector3& v1, const Vector3& v2,
		real inverseMass, real k, real l) {
	addInternalSpring(v1, v2, inverseMass, k, l);
}

void ParticleWorld::addSpringCircle(const Vector3& origin, real r,
		real inverseMass, real k, int qty) {
	real pi = 3.141592653589793238462643383279502884197169399375105820;

	real distance = (real) 2 * pi / qty;
	real l = 0;

	Particle * start = new Particle(origin + Vector3(r, 0, 0), inverseMass);

	Particle * p1 = start;
	Particle * p2;

	this->particles.push_back(start);

	for (double angle = distance; angle < 2 * pi; angle += distance) {

		p2 = new Particle(
				origin + (Vector3(r * cos(angle), r * sin(angle), 0)),
				inverseMass);

		this->particles.push_back(p2);

		this->interactions.push_back(new ParticleInteraction(p1, p2,
				new SpringForce(k, l, p2)));
		this->interactions.push_back(new ParticleInteraction(p2, p1,
				new SpringForce(k, l, p1)));

		p1 = p2;
	}

	// Add last spring
	this->interactions.push_back(new ParticleInteraction(start, p2,
			new SpringForce(k, l, p2)));
	this->interactions.push_back(new ParticleInteraction(p2, start,
			new SpringForce(k, l, start)));
}

void ParticleWorld::addField(Force * field) {
	this->fields.push_back(field);

	list<Particle *>::iterator itr;
	for (itr = particles.begin(); itr != particles.end(); itr++)
		(*itr)->addForce(field);
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
 *
 * TODO: Convertir esto en  n~#particulas threads, sincronizados con un monitor
 */
void ParticleWorld::integrate() {
	list<Particle *>::iterator itr;
	bool integrating = true;
	integrating = particles.empty() ? false : true;

	// Finishes when every particle finishes (they all have the same step)
	while (integrating) {

		// Integrate step
		for (itr = particles.begin(); itr != particles.end(); itr++)
			integrating = !((*itr)->integrate(time, precision)) && integrating;

		// Apply step
		for (itr = particles.begin(); itr != particles.end(); itr++)
			(*itr)->applyStep(precision);
	}
}

/**
 * TODO: Terminar esto.
 * Falta:
 * 	- armar mutex/cond var
 *  - sincronizar
 *  - acoplar con clase
 *  - hacerla global (sino no se puede)
 */
void ParticleWorld::integrateNParticlesThread(void * lowerBound) {
	int index = (int) lowerBound;
	bool integrating = true;
	integrating = particles.empty() ? false : true;
	vector<Particle *> vector;

	while (integrating) {
		for (int i = index; i < this->particlesPerThread; i++)
			integrating = !(vector[i]->integrate(time, precision))
					&& integrating;

		/*
		 *  SYNCHRONIZE WITH MONITOR HERE
		 *  Wait till other threads finished integrating this step to continue
		 */
	}

	// return, destroy thread
}

void ParticleWorld::resolveCollisions() {
	//TODO
}

// PARA TESTEAR!!!
void ParticleWorld::render() {
	// Draw Particles
	list<Particle *>::iterator i;
	list<Particle *>::iterator k;

	/*

	glColor3f(1.0, 1.0, 1.0);
	for (i = particles.begin(); i != particles.end(); i++) {

		Vector3 kPos = (*i)->getData().getPosition();
		Vector3 kVel = (*i)->getData().getVelocity();

		if (kVel.magnitude() > 20) {
			kVel.normalize();
			kVel *= 10;
		} else {
			kVel += Vector3(0.1, 0.1, 0.1);
		}

		kVel = Vector3(1, 1, 1);

		glColor4f(1, 1, 1, 1);
		glLineWidth(2);
		glBegin(GL_LINES);
		{
			glVertex3f(kPos.getX(), kPos.getY(), kPos.getZ());
			glVertex3f(kPos.getX() + kVel.getX(), kPos.getY() + kVel.getY(),
					kPos.getZ() + kVel.getZ());
		}
		glEnd();
	}
	/*
	 list<Vector3> path = (*i)->getPath();
	 list<Vector3>::iterator line;

	 glColor4f(1, 1, 1, 0.2);
	 glLineWidth(1);
	 glBegin(GL_LINES);

	 for (line = path.begin(); line != path.end(); line++)
	 glVertex3f((*line).getX(), (*line).getY(), (*line).getZ());

	 glEnd();
	 }
	 */
	list<ParticleInteraction *>::iterator itr;

	glLineWidth(2);
	glColor3f(1.0, 1.0, 1.0);
	for (itr = interactions.begin(); itr != interactions.end(); itr++)
		if ((*itr)->isDual()) {
			ParticleData d1 = (*itr)->getParticleData();
			ParticleData d2 = (*itr)->getOtherParticleData();

			glBegin(GL_LINES);
			glVertex3f(d1.getPosition().getX(), d1.getPosition().getY(),
					d1.getPosition().getZ());
			glVertex3f(d2.getPosition().getX(), d2.getPosition().getY(),
					d2.getPosition().getZ());
			glEnd();
		}

}

real ParticleWorld::getTime() {
	return time;
}
