/*
 * GameEngine.cpp
 *
 *  Created on: Mar 26, 2011
 *      Author: mariano
 */

#include "../include/GameEngine.h"

GameEngine::GameEngine() {

	srand(time(NULL));
	world = new ParticleWorld(.05);

	ballGroup = ParticleGroupPtr(new ParticleGroup(Vector3(0, 0, 1), true));
	ballGroup->addField(new ConstantForce(500, Vector3(0, -1, 0)));

	SpherePtr sphere(new Sphere(1));
	sphere->setScale(Vector3(10000, 10000, 10000));
	ballGroup->setBoundingShape(sphere);
	world->addParticleGroup(ballGroup);

	// TEST FOR FUTURE ADAPTERS:
	// FIRST CONSTRUCT PHYSICS CONTEXT
	ParticleGroupPtr g = ParticleGroupPtr(new ParticleGroup(Vector3(), false));
	world->addParticleGroup(g);

	RigidBody * rg1 = new RigidBody(ShapePtr(new FinitePlane(500, 500)));
	g->addParticle(rg1);

	ShapePtr shape(new FinitePlane(500, 500));
	shape->setPosition(Vector3(0, 0, 4));
	RigidBody * rg2 = new RigidBody(shape);
	rg2->getCollisionShape()->setRotation(Vector3(3.14 / 2.0, 0, 0));
	g->addParticle(rg2);

	// GRAPHICS CONTEXT
	Mesh * plane1 = new MeshPlane();
	plane1->getTransform()->setScale(Vector3(250, 250, 250));
	plane1->setRenderer(new GLMeshRenderer(plane1));
	gEngine.addMesh(plane1);

	Mesh * plane2 = new MeshPlane();
	plane2->getTransform()->setScale(Vector3(250, 250, 250));
	plane2->setRenderer(new GLMeshRenderer(plane2));
	gEngine.addMesh(plane2);

	// AND CONSTRUCT GAME OBJECT
	GameObject * g1 = new StaticObject(plane1, rg1);
	objects.push_back(g1);

	GameObject * g2 = new StaticObject(plane2, rg2);
	objects.push_back(g2);

	mainCamera = gEngine.get3DLayer()->getCamera();

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
