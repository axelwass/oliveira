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

void testParticleCollision() {

	ParticleWorld world(.3);

	/*
	 Emitter * emitter = new DirectionalEmitter(&world, Vector3(0, 200, 0),
	 Vector3(0, -1, 0), 450, 1, 5, .1);

	 world.addEmitter(emitter);

	 emitter->getParticleGroup()->addField(new ConstantForce(1,
	 Vector3(0, -1, 0)));
	 */

	ParticleGroupPtr g = ParticleGroupPtr(new ParticleGroup(Vector3(0, 100, 0),
			false));

	g->addParticle(.01, Vector3(0, 200, 0));
	g->addField(new ConstantForce(300, Vector3(0, -1, 0)));

	world.addParticleGroup(g);

	ParticlePlane plane(&world, Vector3(0, 0, 0), 500, 500, 15, 15, 60);

	int time = SDL_GetTicks();
	int nextTime;
	int qtyFrames = 0;
	real avg = 0;

	GraphicsEngine gEngine;
	EventsManager events;

	while (gEngine.update()) {

		events.update();

		gEngine.render();

		world.runPhysics();
		world.render();

		nextTime = SDL_GetTicks() - time;
		time = time + nextTime;

		avg += 1000.0 / nextTime;
		qtyFrames++;
	}

	printf("Average framerate: %f\n", avg / qtyFrames);

	// El octree hace efecto solo en las colisiones, OJO

	// Average framerate: 25.377089 con gravedad + colisiones con octree, 50 particulas
	// Average framerate: 15.646843 con gravedad + colisiones SIN octree, 50 particulas

	// Average framerate: 5.709004 con gravedad + colisiones SIN octree, 100 particulas
	// Average framerate: 12.892283 con gravedad + colisiones con octree, 100 particulas

	// Buena onda, el octree es mucho mejor =D
}

void testText() {
	GraphicsEngine gEngine;
	EventsManager events;

	real x, y, z, w, h;

	x = 0;
	y = 0;
	z = 0;

	Texture * texture = new TextTexture("Yayy! probando", 60, Color(255, 255, 255));
	texture->LoadTexture();

	w = texture->getWidth();
	h = texture->getHeight();

	while (gEngine.update()) {

		events.update();

		gEngine.render();

		texture->BindTexture();

		// Draw rectangle
		glBegin(GL_QUADS);

		glTexCoord2i(0, 0);
		glVertex3f(x, y, -z);

		glTexCoord2i(1, 0);
		glVertex3f(x + w, y, -z);

		glTexCoord2i(1, 1);
		glVertex3f(x + w, y + h, -z);

		glTexCoord2i(0, 1);
		glVertex3f(x, y + h, -z);

		glEnd();

		texture->UnbindTexture();

	}
}

int main(int argc, char *argv[]) {

	srand(time(NULL));

	// initialize glut!
	glutInit(&argc, (char**) argv);

	testText();
	return 0;

	testParticleCollision();
	return 0;
}
