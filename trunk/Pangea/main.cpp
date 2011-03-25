/*
 * main.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "Physics/Physics.h"
#include "Graphics/Graphics.h"
#include "Events/Events.h"

#include <GL/glut.h>

// LEER todo.txt
int main(int argc, char *argv[]) {

	srand(time(NULL));

	// initialize glut!
	glutInit(&argc, (char**) argv);

	ParticleWorld world(.05);

	ParticleGroupPtr g = ParticleGroupPtr(new ParticleGroup(
			Vector3(20, 100, 0), true));

	g->addParticle(.1, Vector3(0, 100, 0));
	g->addField(new ConstantForce(1600, Vector3(0, -1, 0)));

	ShapePtr shape = ShapePtr(new FinitePlane(500, 500));
	RigidBody rg(shape);

	g->addParticle(&rg);

	world.addParticleGroup(g);

	GraphicsEngine gEngine;
	EventsManager events;

	while (gEngine.update()) {

		events.update();
		gEngine.render();

		world.runPhysics();
		world.render();

		glLoadIdentity();
		glutWireCube(500);
	}

	return 0;
}
