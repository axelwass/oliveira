/*
 * ParticleGroup.h
 *
 *  Created on: Feb 14, 2011
 *      Author: mmerchan
 */

#include "../octree/Octree.h"
#include "Particle.h"
#include "../force/InterParticleForce.h"
#include "ParticleData.h"
#include <tr1/memory>
using namespace std;

#ifndef PARTICLEGROUP_H_
#define PARTICLEGROUP_H_

class ParticleGroup;

typedef tr1::shared_ptr<ParticleGroup> ParticleGroupPtr;

class ParticleGroup: public Positionable<ParticleGroup> , public Collisionable {
private:

	// Useful for all particle related
	typedef tr1::shared_ptr<Octree<Particle> > OctreePtr;

	OctreePtr octree;
	list<Particle *> particles;

	list<Force *> fields;

	bool selfCollisions;
	Vector3 centerOfMass;
	SpherePtr boundingShape;

	void repositionCollided(Particle * p1, Particle * p2);

public:
	~ParticleGroup() {
		//cout << "Grupo destruido" << endl;
	}

	CollisionableType getCollisionableType() {
		return C_ParticleGroup;
	}

	void setBoundingShape(SpherePtr shape) {
		this->boundingShape = shape;
	}

	// Empty position is group's position if it has empty particles
	ParticleGroup(const Vector3& emptyPosition, bool selfCollisions);

	Vector3 getPosition();

	int getParticleCount();

	// I hate this
	ParticleGroup * getThis();

	Particle * addParticle(real inverseMass, const Vector3& pos,
			const Vector3& vel = Vector3());

	Particle * addParticle(Particle * p);

	void addField(Force * field);

	void addInternalForce(InterParticleForce * f);

	list<Particle *>& getParticles();

	bool integrateStep(real time, real step);

	void applyStep(real step);

	void resolveInternalCollisions();

	bool resolveCollision(Collisionable& other, IntersectionData& data);

	ShapePtr getCollisionShape();

	// test
	void render();
};

#endif /* PARTICLEGROUP_H_ */
