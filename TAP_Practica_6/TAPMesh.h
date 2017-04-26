#pragma once

#include <vector>
#include <glut.h>
#include <iostream>

#include "igvMaterial.h"
#include "igvFuenteLuz.h"

class TAPMesh {

	std::vector<int> caras;
	std::vector<float> normales;
	std::vector<float> vertices;

	int *carasP;
	float *normalesP;
	float *verticesP;

	float X;
	float Y;
	float Z;

	float X2;
	float Y2;
	float Z2;

	int sum;

	

public:

	bool trans;

	/**
	* Constructores
	*/

	TAPMesh();
	TAPMesh(std::vector<float> _vertices, std::vector<float> _normales, std::vector<int> _caras);

	/**
	* Funcion encargada de pintar la malla
	*/

	void drawObjectC(int j);

	/**
	* Funicones de translacion y rotacion
	*/

	void trasladar(float x, float y, float z) {
		X2 += x;
		Y2 += y;
		Z2 += z;
		trans = true;

		if (sum == 0)sum = 1;
	}

	void trasladarhijo(float x, float y, float z) {
		X2 = x;
		Y2 = y;
		Z2 = z;
		trans = true;

		if (sum == 0)sum = 1;
	}

	void desaplicartranslacion() {
		X = 0;
		Y = 0;
		Z = 0;

		X2 = 0;
		Y2 = 0;
		Z2 = 0;

		trans = false;

		sum = 0;
	}

	void rotar(int j, int k, int x, int y, int z, int rot) {
		GLfloat luz0[4];
		GLfloat color_malla[3];
		if (k == 1) {
			luz0[0] = 1;
			luz0[1] = 0;
			luz0[2] = 0;
			luz0[3] = 1;
			color_malla[0] = 1;
			color_malla[1] = 0;
			color_malla[2] = 0;
		}
		else {
			luz0[0] = 0;
			luz0[1] = 0;
			luz0[2] = 0;
			luz0[3] = 1;
			color_malla[0] = 0;
			color_malla[1] = 0;
			color_malla[2] = 0;
		}

		glEnable(GL_LIGHT0);

		//glBegin(GL_POINTS);
		//for (float i = 0.0f; i < 20; i += 0.1f) {
		//	glVertex3d(-i, 0, 0);
		//	glVertex3d(0, i, 0);
		//	glVertex3d(0, 0, i);
		//}
		//glEnd();

		glPushMatrix();
			
		std::cout << Y << " - " << Y2 << std::endl;

			if (trans){
				if (Y == 5 && Y2 != 5 && sum == 1)sum = -1;
				if (Y == -4 && Y2 != -4 && sum == -1)sum = 1;
			}

			switch (j) {
			case 2:
				glTranslatef(X, Y + sum, Z);
				glTranslatef(-0.9, 1.15 , 1.15);
				glRotatef(rot, x, y, z);
				glTranslatef(0.9, -1.15 , -1.15);

				break;
			case 3:
				glTranslatef(X, Y + sum, Z);
				glTranslatef(-1.75, 2.6, 1.25);
				glRotatef(rot, x, y, z);
				glTranslatef(1.75,-2.6 , -1.25);

				break;
			case 4:
				glTranslatef(X, Y + sum, Z);
				glTranslatef(-0.15, 2.6, 1.15);
				glRotatef(rot, x, y, z);
				glTranslatef(0.15, -2.6, -1.15);

				break;
			case 7:
				glTranslatef(X, Y + sum, Z);
				glTranslatef(-0.9, 3.0, 1.15);
				glRotatef(rot, x, y, z);
				glTranslatef(0.9, -3.0, -1.15);

				break;
			case 8:
				glTranslatef(X, Y + sum, Z);
				glTranslatef(-1.15, 1.15, 1.15);
				glRotatef(rot, x, y, z);
				glTranslatef(1.15, -1.15, -1.15);

				break;
			case 9:
				glTranslatef(X, Y + sum, Z);
				glTranslatef(-0.5, 1.15, 1.15);
				glRotatef(rot, x, y, z);
				glTranslatef(0.5, -1.15 , -1.15);
				//glTranslatef(-X, -Y, -Z);

			case 13:

				break;
			case 14:

				break;

			}
			
			X = X2;
			Y = Y2;
			Z = Z2;

			//glLightfv(GL_LIGHT0, GL_AMBIENT, luz0);
			igvFuenteLuz l(GL_LIGHT0, igvPunto3D(5.0, 5.0, 0.0), igvColor(0.0, 0.0, 0.0, 1.0), igvColor(1.0, 1.0, 1.0, 1.0), igvColor(1.0, 1.0, 1.0, 1.0), 1.0, 0.0, 0.0);
			l.aplicar();
			glMaterialfv(GL_FRONT, GL_EMISSION,  color_malla );

			glShadeModel(GL_SMOOTH);

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, verticesP);

			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, 0, normalesP);

			glDrawElements(GL_TRIANGLES, caras.size(), GL_UNSIGNED_INT, carasP);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);

		glPopMatrix();
	}

	~TAPMesh();
};

