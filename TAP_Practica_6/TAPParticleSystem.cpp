#include "TAPParticleSystem.h"

#include <glut.h>
#include <iostream>

TAPParticleSystem::TAPParticleSystem() {
	numParticles = 1000;

	systemPull.y = 0.0005;
	systemPull.x = 0.0f;
	systemPull.z = 0.0f;

	for (int i = 0; i < numParticles; i++) {
		crearParticula();
	}

	texture[0] = igvTextura("particle_mask.raw", 256, 256);
	texture[1] = igvTextura("particle.raw", 256, 256); 
}

TAPParticleSystem::TAPParticleSystem(int _numParticles) {
	numParticles = _numParticles;

	systemPull.y = 0.0005;
	systemPull.x = 0.0f;
	systemPull.z = 0.0f;

	for (int i = 0; i < numParticles; i++) {
		crearParticula();
	}

	texture[0] = igvTextura("particle_mask.raw", 256, 256);
	texture[1] = igvTextura("particle.raw", 256, 256);
}

void TAPParticleSystem::crearParticula() {
	Particle p;

	p.lifespan = (((rand() % 10 + 1))) / 10.0f;
	p.smoke = false;

	p.age = 0.0f;
	p.scale = 0.25f;
	p.direction = 0;

	p.position.x = 0;
	p.position.y = -15;
	p.position.z = 0;

	p.movement.x = (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.007) - (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.007);
	p.movement.y = ((((((5) * rand() % 11) + 5)) * rand() % 11) + 1) * 0.02;
	p.movement.z = (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.007) - (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.007);

	p.color.x = 1.0f;
	p.color.y = 0.95f;
	p.color.z = 0.8f;

	p.pull.x = 0.0f;
	p.pull.y = 0.0f;
	p.pull.z = 0.0f;

	particles.push_back(p);
}

void TAPParticleSystem::crearParticula(int i) {

	particles[i].lifespan = (((rand() % 10 + 1))) / 10.0f;
	particles[i].smoke = false;

	particles[i].age = 0.0f;
	particles[i].scale = 0.25f;
	particles[i].direction = 0;

	particles[i].position.x = 0;
	particles[i].position.y = -15;
	particles[i].position.z = 0;

	particles[i].movement.x = (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.007) - (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.007);
	particles[i].movement.y = ((((((5) * rand() % 11) + 5)) * rand() % 11) + 1) * 0.02;
	particles[i].movement.z = (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.007) - (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.007);

	particles[i].color.x = 1.0f;
	particles[i].color.y = 0.95f;
	particles[i].color.z = 0.8f;

	particles[i].pull.x = 0.0f;
	particles[i].pull.y = 0.0f;
	particles[i].pull.z = 0.0f;
}

void TAPParticleSystem::updateParticle() {
	for (int i = 0; i < numParticles; i++) {
		particles[i].age = particles[i].age + 0.02;

		if (particles[i].smoke) {
			particles[i].scale = particles[i].scale + 0.001;
		}

		particles[i].direction = particles[i].direction + ((((((int)(0.5) * rand() % 11) + 1)) * rand() % 11) + 1);

		particles[i].position.x = particles[i].position.x + particles[i].movement.x + particles[i].pull.x;
		particles[i].position.y = particles[i].position.y + particles[i].movement.y + particles[i].pull.y;
		particles[i].position.z = particles[i].position.z + particles[i].movement.z + particles[i].pull.z;

		particles[i].pull.x = particles[i].pull.x + systemPull.x;
		particles[i].pull.y = particles[i].pull.y + systemPull.y;
		particles[i].pull.z = particles[i].pull.z + systemPull.z;

		// Cambiar el color de las particulas del fuego con el tiempo
		if (!particles[i].smoke) {
			float temp = particles[i].lifespan / particles[i].age;
			if (temp < 1.75) {
				particles[i].color.x = 1.0f;
				particles[i].color.y = 0.25f;	//ROJAS
				particles[i].color.z = 0.0f;
			}
			else if (temp < 3.0) {
				particles[i].color.x = 1.0f;
				particles[i].color.y = 0.9f;	//COLOR ORO
				particles[i].color.z = 0.0f;
			}
			else if (temp < 10.0) {
				particles[i].color.x = 1.0f;
				particles[i].color.y = 1.0f;	//AMARILLO
				particles[i].color.z = 0.0f;
			}
			else {
				particles[i].color.x = 1.0f;
				particles[i].color.y = 0.95f;	//AMARILLO INICIAL
				particles[i].color.z = 0.8f;
			}
		}


		if (!particles[i].smoke) {
			if (particles[i].age > particles[i].lifespan || particles[i].position.y > 35 || particles[i].position.y < -25 || particles[i].position.x > 40 || particles[i].position.x < -40) {
				int temp = rand() % 100;
				if (temp < 10) {
					pasarAHumo(i);
				} else {
					crearParticula(i);
				}	
			}
		} else if (particles[i].smoke) {
			if (particles[i].age > particles[i].lifespan || particles[i].position.y > 45 || particles[i].position.y < -35 || particles[i].position.y > 80 || particles[i].position.y < -80) {
				crearParticula(i);
			}
		}
	}
}

void TAPParticleSystem::pasarAHumo(int i){
	particles[i].lifespan = (((rand() % 125 + 1) / 10.0f) + 5);
	particles[i].age = 0.0f;
	particles[i].scale = 0.25f;
	particles[i].direction = 0;
	particles[i].smoke = true;

	particles[i].movement.x = (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.0035) - (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.0035);
	particles[i].movement.y = ((((((5) * rand() % 11) + 3)) * rand() % 11) + 7) * 0.015;
	particles[i].movement.z = (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.0015) - (((((((2) * rand() % 11) + 1)) * rand() % 11) + 1) * 0.0015);

	particles[i].color.x = 0.7f;
	particles[i].color.y = 0.7f;
	particles[i].color.z = 0.7f;
}

void TAPParticleSystem::modifySystemPull(float x, float y, float z){
	systemPull.x += x;
	systemPull.y += y;
	systemPull.z += z;
}

int TAPParticleSystem::getNumOfParticles(){
	return numParticles;
}

float TAPParticleSystem::getXPos(int i){
	return particles[i].position.x;
}

float TAPParticleSystem::getYPos(int i){
	return particles[i].position.y;
}

float TAPParticleSystem::getZPos(int i){
	return particles[i].position.z;
}

float TAPParticleSystem::getRColor(int i){
	return particles[i].color.x;
}

float TAPParticleSystem::getGColor(int i){
	return particles[i].color.y;
}

float TAPParticleSystem::getBColor(int i){
	return particles[i].color.z;
}

float TAPParticleSystem::getScale(int i){
	return particles[i].scale;
}

float TAPParticleSystem::getDirection(int i){
	return particles[i].direction;
}

float TAPParticleSystem::getAlpha(int i){
	return (1 - particles[i].age / particles[i].lifespan);
}

void TAPParticleSystem::pintarSistemaPArticulas(){
	updateParticle();

	for (int i = 0; i < numParticles; i++) {
		glPushMatrix();
		
		std::cout << getRColor(i) << " - " << getGColor(i) << " - " << getBColor(i) << " - " << getAlpha(i) << std::endl;

		glColor4f(getRColor(i), getGColor(i), getBColor(i), getAlpha(i));
		
		glTranslatef(getXPos(i), getYPos(i), getZPos(i) /* + zoom? */);
		
		glRotatef(getDirection(i) - 90, 0, 0, 1);
		
		glScalef(getScale(i), getScale(i), getScale(i));

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		texture[0].aplicar();

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(-1, -1, 0);
		glTexCoord2d(1, 0);
		glVertex3f(1, -1, 0);
		glTexCoord2d(1, 1);
		glVertex3f(1, 1, 0);
		glTexCoord2d(0, 1);
		glVertex3f(-1, 1, 0);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		texture[1].aplicar();

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(-1, -1, 0);
		glTexCoord2d(1, 0);
		glVertex3f(1, -1, 0);
		glTexCoord2d(1, 1);
		glVertex3f(1, 1, 0);
		glTexCoord2d(0, 1);
		glVertex3f(-1, 1, 0);
		glEnd();

		glEnable(GL_DEPTH_TEST);

		glPopMatrix();
	}
}

TAPParticleSystem::~TAPParticleSystem() {}
