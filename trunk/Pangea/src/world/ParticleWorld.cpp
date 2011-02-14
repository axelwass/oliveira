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
	particleOctree = OctreePtr(new Octree<Particle> (Vector3(), 1, 100, true));
}

/*
 * The main function of the engine
 */
void ParticleWorld::runPhysics() {
	particleEmission();
	integrate();
	time += precision;

	particleOctree->update();
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
	this->particleOctree->put(p);

	return p;
}

void ParticleWorld::addParticleInteraction(Particle * p1, Particle * p2,
		Force * f) {
	ParticleInteraction * i = new ParticleInteraction(p1, p2, f);
	this->interactions.push_back(i);
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

		// To prevent intersection problems
		resolveCollisions();

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

void ParticleWorld::repositionCollided(Particle * p1, Particle * p2) {

	// from 1 to 2
	Vector3 dist = p1->getPosition() - p2->getPosition();

	real diff = fabs(dist.magnitude() - 5 * 2) + 1; // 5 is radius of particle for now

	// only finite for now...
	real ma = p1->getData().getMass();
	real mb = p2->getData().getMass();

	// coeffs to balance repositioning
	real ca = ma / (ma + mb);
	real cb = mb / (ma + mb);

	dist.normalize();

	ParticleData d1 = p1->getData();
	d1.setPosition(d1.getPosition() + dist * diff * .5 * cb);
	p1->setData(d1);

	ParticleData d2 = p2->getData();
	d2.setPosition(d2.getPosition() - dist * diff * .5 * ca);
	p2->setData(d2);
}

void ParticleWorld::resolveCollisions() {
	list<Particle *>::iterator p;
	for (p = particles.begin(); p != particles.end(); p++) {

		Sphere * sphere = new Sphere(10);
		sphere->setPosition((*p)->getPosition());

		list<Positionable<Particle> *> closestElements =
				particleOctree->getIntersectionElements(sphere);

		//cout << particleOctree->getElementCount() << endl;

		//cout << closestElements.size() << endl;

		list<Positionable<Particle> *>::iterator closeP;
		for (closeP = closestElements.begin(); closeP != closestElements.end(); closeP++) {

			Particle * other = (*closeP)->getThis();

			if (other != (*p)) {

				IntersectionData data = (*p)->checkCollision(*other);
				if (data.hasIntersected()) {
					repositionCollided(*p, other);
					(*p)->resolveCollision(*other, data);
				}
			}
		}
	}
}

// PARA TESTEAR!!!
void ParticleWorld::render() {

	//particleOctree->render(NULL, true);

	// Draw Particles
	list<Particle *>::iterator i;
	list<Particle *>::iterator k;

	glColor3f(1.0, 1.0, 1.0);
	for (i = particles.begin(); i != particles.end(); i++) {

		Vector3 kPos = (*i)->getData().getPosition();
		Vector3 kVel = (*i)->getData().getVelocity();

		glTranslatef(kPos.getX(), kPos.getY(), kPos.getZ());

		glutWireSphere(5, 10, 10);

		glTranslatef(-kPos.getX(), -kPos.getY(), -kPos.getZ());

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
	 *
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
	 */
}

real ParticleWorld::getTime() {
	return time;
}
