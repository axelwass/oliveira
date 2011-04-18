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
	world = new ParticleWorld(.1);

	ballGroup = ParticleGroupPtr(new ParticleGroup(Vector3(), true));
	ballGroup->addField(new ConstantForce(5, Vector3(0, -1, 0)));
	world->addParticleGroup(ballGroup);
/*
	Particle * p2 = ballGroup->addParticle(1, Vector3(0, 20, 0), Vector3(0, 1,
			0));
	// GRAPHICS CONTEXT
	Mesh * ball2 = MeshLoader::load("sphere.obj");
	ball2->setRenderer(new GLMeshRenderer(ball2, true));
	gEngine.addMesh(ball2);

	// AND CONSTRUCT GAME OBJECT
	GameObject * ballObject2 = new StaticObject(ball2, p2);
	objects.push_back(ballObject2);

	Particle * p1 = ballGroup->addParticle(1, Vector3(0, 50, 0), Vector3(0, -1,
			0));
	// GRAPHICS CONTEXT
	Mesh * ball1 = MeshLoader::load("sphere.obj");
	ball1->setRenderer(new GLMeshRenderer(ball1, true));
	gEngine.addMesh(ball1);

	// AND CONSTRUCT GAME OBJECT
	GameObject * ballObject1 = new StaticObject(ball1, p1);
	objects.push_back(ballObject1);
*/
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
