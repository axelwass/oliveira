/*
 * GameEngine.cpp
 *
 *  Created on: Mar 26, 2011
 *      Author: mariano
 */

#include "../include/UI/Console.h"
#include "../include/GameEngine.h"

GameEngine::GameEngine() {

	srand(time(NULL));
	world = new ParticleWorld(.01);

	ballGroup = ParticleGroupPtr(new ParticleGroup(Vector3(), true));
	ballGroup->addField(new ConstantForce(5, Vector3(0, -1, 0)));
	world->addParticleGroup(ballGroup);

	RigidBody * rg1 = new RigidBody(ShapePtr(new FinitePlane(500, 500)));
	ballGroup->addParticle(rg1);

	// GRAPHICS CONTEXT
	Mesh * plane1 = new MeshPlane();
	plane1->getTransform()->setScale(Vector3(500, 500, 500));
	plane1->setRenderer(new GLMeshRenderer(plane1));
	gEngine.addMesh(plane1);

	// AND CONSTRUCT GAME OBJECT
	GameObject * g1 = new StaticObject(plane1, rg1);
	objects.push_back(g1);

	mainCamera = gEngine.get3DLayer()->getCamera();

	// Now add a console
	UIOverlay * ui = gEngine.getUIOverlay();
	ui->addUIComponent(new Console(Vector3(10, 480, 0), 300, 100, Color(100,
			100, 100, 150)));

	mainLoop();
}

void GameEngine::mainLoop() {

	while (gEngine.update()) {

		events.update();

		list<GameObject *>::iterator g;
		for (g = objects.begin(); g != objects.end(); g++)
			(*g)->process();

		world->runPhysics();
		gEngine.render();

	}
}

void GameEngine::end() {

}
