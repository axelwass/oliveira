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

	ParticleWorld world(0.05);

	world.addParticle(1/2.0,Vector3(0,0,0));

	for(int i=0;i<100;i++)
		world.addParticle(1/2.0,Vector3(-200 + rand()%400,-200 + rand()%400,0));

	world.addWorldInteraction(new ConstantForce(9.81, Vector3(0,-1,0)));

	//world.addPerParticleInteraction(new GravitationalForce());

	while (window.Refresh(1)) {
		world.runPhysics();
		world.render();
	}

	return 1;
}
