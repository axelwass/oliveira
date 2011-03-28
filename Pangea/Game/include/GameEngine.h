/*
 * GameEngine.h
 *
 *  Created on: Mar 26, 2011
 *      Author: mariano
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include "../Game.h"
#include "Core/GameObject.h"

#include "Objects/StaticObject.h"

class GameEngine: public KeyListener {
private:

	list<GameObject *> objects;

	ParticleWorld * world;
	GraphicsEngine gEngine;
	EventsManager events;

	// TODO erase this...
	Camera * mainCamera;
	ParticleGroupPtr ballGroup;

public:
	GameEngine();

	void mainLoop();

	void end();

	// should be key event ...
	virtual void onKeyDown(int key) {

		if (key != ' ')
			return;

		Vector3 pos = mainCamera->getPosition();
		Vector3 d = mainCamera->getDirection();

		Particle * p = ballGroup->addParticle(.05, pos, d * 50);

		// GRAPHICS CONTEXT
		Mesh * ball = MeshLoader::load("sphere.obj");
		ball->setRenderer(new GLMeshRenderer(ball));
		gEngine.addMesh(ball);

		// AND CONSTRUCT GAME OBJECT
		GameObject * ballObject = new StaticObject(ball, p);
		objects.push_back(ballObject);
	}

	virtual void onKeyUp(int key) {

	}

};

#endif /* GAMEENGINE_H_ */
