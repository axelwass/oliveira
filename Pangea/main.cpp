/*
 * main.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "include/Vector3.h"

#include "include/force/ConstantForce.h"
#include "include/force/SpringForce.h"
#include "include/force/GravitationalForce.h"
#include "include/force/FlashGravityForce.h"

#include "include/particle/ParticleData.h"
#include "include/particle/Particle.h"
#include "include/particle/ParticleRope.h"
#include "include/particle/ParticleBridge.h"

#include "include/emitter/Emitter.h"
#include "include/emitter/DirectionalEmitter.h"
#include "include/world/ParticleWorld.h"
#include "include/ode/RK4.h"
#include "include/precision.h"
#include "MainWindow.h"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
using namespace std;

/* ME QUEDE EN: emisores, particle groups y fields
 * 0) Analizar la utilidad de tener particleGroups.
 * 1) repensar las interacciones. DIF. entre interaccion VS campo de fuerza (fields)
 * 2) colisiones
 * 3) octree!
 * 4) apl. octree a colisiones y interacciones
 * 5) colisiones entre pasos
 * 6) cuando ande todo esto, usar punteros mas seguros (shared_ptr)
 * n!) decorator de decorators, game object
 */

int main(int argc, char *argv[]) {

	MainWindow window(1200, 600);
	srand(time(NULL));

	ParticleWorld world(.08);

	DirectionalEmitter e1 = DirectionalEmitter(&world, Vector3(-100, 0, 0),
			Vector3(0, -1, 0), .4, 0, 10, 1);

	world.addEmitter(&e1);

	world.addField(new ConstantForce(.5, Vector3(0, 1, 0)));

	/*
	 ParticleBridge bridge(&world, Vector3(-500, 0, 0), Vector3(-100, 0, 0),
	 100, .015, 50);

	 ParticleBridge bridge2(&world, Vector3(-500, -300, 0),
	 Vector3(500, -300, 0), 50, .15, 120);

	 /*
	 Particle * ropeBase = (rope.getRope().front());
	 ParticleData data = ropeBase->getData();

	 //	Particle * p =	world.addParticle(1, Vector3(0, 50, 0), Vector3(10,-40,0));

	 //world.addParticleInteraction(p, NULL, new ConstantForce(10, Vector3(0,1,0)));


	 /*world.addParticle(1 / (double) 80000, Vector3(150, 0, 0),
	 Vector3(150, 0, 0));
	 /*
	 for (int i = 0; i < 100; i++) {
	 world.addParticle(1 / 5.0, Vector3(-50 + rand() % 100, -50 + rand()
	 % 100, 0), Vector3(-5 + rand() % 10, -5 + rand() % 10, 0));
	 }

	 /*
	 for (int r = 1; r < 4; r++)
	 for (double angle = 0; angle < 2 * 3.14; angle += 0.1)
	 world.addParticle(1 / 2.0, Vector3(-150 + cos(angle) * 50 * r, sin(
	 angle) * r * 50, 0));
	 */
	//world.addWorldInteraction(new ConstantForce(9.81, Vector3(0,-1,0)));

	//		world.addPerParticleInteraction(new GravitationalForce());

	//	world.addSpring(Vector3(-100,0,0),Vector3(100,0,0),
	//		1, 5, 100);

	//world.addSpringCircle(Vector3(0, 0, 0), 300, 1 / 50.0, 100, 50);

	//world.addPerParticleInteraction(new FlashGravityForce());

	world.updateForces();

	world.printParticles();

	while (window.Refresh(0)) {
		/*
		 data.setPosition(Vector3(data.getPosition().getX(),
		 sin(world.getTime()*4)*150, data.getPosition().getZ()));
		 ropeBase->setData(data);
		 */
		world.render();
		world.runPhysics();
	}

	return 1;
}
