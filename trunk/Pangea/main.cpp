/*
 * main.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "include/Vector3.h"
#include "include/force/ConstantForce.h"
#include "include/force/GravitationalForce.h"
#include "include/particle/ParticleData.h"
#include "include/particle/Particle.h"
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

/*
 * 4) colisiones entre pasos
 */
int main(int argc, char *argv[]) {

	MainWindow window(1200, 600);

	srand(time(NULL));

	ParticleWorld world(0.08);

	for (double angle = 0; angle < 2 * 3.14; angle += 0.1)
		world.addParticle(1 / 2.0, Vector3(-150 + cos(angle) * 50, sin(angle)
				* 50, 0));

	for (double angle = 0; angle < 2 * 3.14; angle += 0.1)
		world.addParticle(1 / 2.0, Vector3(150 + cos(angle) * 50, sin(angle)
				* 50, 0));

	//world.addWorldInteraction(new ConstantForce(9.81, Vector3(0,-1,0)));

	world.addPerParticleInteraction(new GravitationalForce());

	while (window.Refresh(1)) {
		world.render();
		world.runPhysics();
	}

	return 1;
}
