#include "TAPMesh.h"

TAPMesh::TAPMesh(){
	vertices = std::vector<float>();
	normales = std::vector<float>();
	caras = std::vector<int>();
	X = 0;
	Y = 0;
	Z = 0;

	X2 = 0;
	Y2 = 0;
	Z2 = 0;

	sum = 0;

	trans = false;
}

TAPMesh::TAPMesh(std::vector<float> _vertices, std::vector<float> _normales, std::vector<int> _caras){
	vertices = _vertices;
	normales = _normales;
	caras = _caras;

	verticesP = new float[vertices.size()];
	for (int i = 0; i < vertices.size(); i++) {
		verticesP[i] = vertices[i];
	}

	normalesP = new float[normales.size()];
	for (int i = 0; i < normales.size(); i++) {
		normalesP[i] = normales[i];
	}

	carasP = new int[caras.size()];
	for (int i = 0; i < caras.size(); i++) {
		carasP[i] = caras[i];
	}

	X = 0;
	Y = 0;
	Z = 0;

	X2 = 0;
	Y2 = 0;
	Z2 = 0;

	sum = 0;

	trans = false;
}

void TAPMesh::drawObjectC(int j) {
	GLfloat luz0[4];
	GLfloat color_malla[3];
	if (j == 1) {
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
	
	glPushMatrix();

	glTranslatef(X2, Y2, Z2);
	X = X2;
	Y = Y2;
	Z = Z2;
	std::cout << X << " " << Y << " " << Z << std::endl;
		//glLightfv(GL_LIGHT0, GL_AMBIENT, luz0);
		igvFuenteLuz l(GL_LIGHT0, igvPunto3D(5.0, 5.0, 0.0), igvColor(0.0, 0.0, 0.0, 1.0), igvColor(1.0, 1.0, 1.0, 1.0), igvColor(1.0, 1.0, 1.0, 1.0), 1.0, 0.0, 0.0);
		l.aplicar();
		glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);

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

TAPMesh::~TAPMesh(){}
