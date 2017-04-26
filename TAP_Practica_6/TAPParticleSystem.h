#pragma once

#include <vector>
#include "igvTextura.h"

struct Vector {
	float x;
	float y;
	float z;
};

struct Particle {
	bool smoke; //Para distinguir entre humo o fuego
	float lifespan;
	float age;
	float scale;
	float direction;
	Vector position;
	Vector movement;
	Vector color;
	Vector pull;
};

class TAPParticleSystem{

	Vector systemPull; 
	std::vector<Particle> particles;
	int numParticles;

	igvTextura texture[2];

public:

	/**
	* Constructores
	*/

	TAPParticleSystem();
	TAPParticleSystem(int _numParticles);

	/**
	* Funciones encargadas de crear / actualizar las particulas
	*/

	void crearParticula();
	void crearParticula(int i);
	void updateParticle();
	void pasarAHumo(int i);

	void modifySystemPull(float x, float y, float z);

	/**
	* Metodos Gets y Sets
	*/

	int getNumOfParticles(); 
	float getXPos(int i); 
	float getYPos(int i); 
	float getZPos(int i); 
	float getRColor(int i); 
	float getGColor(int i);
	float getBColor(int i);
	float getScale(int i); 
	float getDirection(int i); 

	//Devuelve la descoloracion de una particula en funcion de su tiempo de vida
	float getAlpha(int i); 

	/**
	* Funcion encargada de pintar el Sistema de Particulas
	*/
	void pintarSistemaPArticulas();

	~TAPParticleSystem();
};

