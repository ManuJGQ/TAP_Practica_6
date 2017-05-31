#include "igvTextura.h"

#include <stdlib.h>
#include <iostream>

// Metodos constructores y destructor

igvTextura::igvTextura() {}

igvTextura::igvTextura(char *fichero) {
	GLubyte *imagen;

	imagen = loadBMPRaw(fichero, alto, ancho);

	glGenTextures(1, &idTextura);
	glBindTexture(GL_TEXTURE_2D, idTextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	delete imagen;
}

igvTextura::igvTextura(const char * filename, int width, int height){
	ancho = width;
	alto = height;
	unsigned char * data;
	FILE * file;
	file = fopen(filename, "rb");
	if (file == NULL) {
		std::cout << "ERROR" << std::endl;
		return;
	}
	std::cout << "LEO" << std::endl;
	data = (unsigned char *)malloc(ancho * alto * 3);
	fread(data, ancho * alto * 3, 1, file);
	fclose(file);
	glGenTextures(1, &idTextura);
	glBindTexture(GL_TEXTURE_2D, idTextura);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);
}

void igvTextura::aplicar(void) {
	glBindTexture(GL_TEXTURE_2D, idTextura);
}

igvTextura::~igvTextura() {
	glDeleteTextures(1, &idTextura);
}
