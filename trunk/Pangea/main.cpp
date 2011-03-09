/*
 * main.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */


#include "Physics/Physics.h"

// LEER todo.txt

void testParticleCollision(MainWindow * window) {

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

	while (window->Refresh(0)) {

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

int main(int argc, char *argv[]) {

	MainWindow window(1200, 600);
	glutInit(&argc, (char**) argv);
	srand(time(NULL));

	testParticleCollision(&window);
	return 0;
}
