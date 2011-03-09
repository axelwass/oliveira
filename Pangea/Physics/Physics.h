/*
 * Physics.h
 *
 *  Created on: Mar 9, 2011
 *      Author: mariano
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_


#include "../Generic/Generic.h"

#include <GL/glut.h>

#include "include/shape/Shape.h"
#include "include/shape/FinitePlane.h"
#include "include/shape/Sphere.h"
#include "include/shape/Cube.h"

#include "include/force/ConstantForce.h"
#include "include/force/SpringForce.h"
#include "include/force/GravitationalForce.h"
#include "include/force/FlashGravityForce.h"

#include "include/particle/ParticleData.h"

#include "include/particle/ParticleGroup.h"
#include "include/particle/Particle.h"
#include "include/particle/constructs/ParticleRope.h"
#include "include/particle/constructs/ParticleBridge.h"

#include "include/particle/constructs/ParticlePlane.h"

#include "include/emitter/Emitter.h"
#include "include/emitter/DirectionalEmitter.h"
#include "include/world/ParticleWorld.h"
#include "include/ode/RK4.h"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include <sys/time.h>

#include "include/octree/Octree.h"

#include <tr1/memory>

using namespace std;


#endif /* PHYSICS_H_ */
