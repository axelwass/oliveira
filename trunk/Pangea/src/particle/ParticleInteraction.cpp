/*
 * ParticleInteraction.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: mmerchan
 */

#include "../../include/particle/ParticleInteraction.h"
#include <stdio.h>

ParticleInteraction::ParticleInteraction(Particle * particle, Particle * other, Force * force){
	if( particle != NULL && other != NULL && force != NULL){
		this->particle = particle;
		this->other = other;
		this->force = force;
		this->active = true;
	}
}

void ParticleInteraction::resolve(){
	if(this->active)
		this->particle->addForce(this->force);
}

void ParticleInteraction::enable(){
	this->active = true;
}

void ParticleInteraction::disable(){
	this->active = false;
}
