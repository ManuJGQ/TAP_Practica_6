#pragma once

#include "TAPMesh.h"

#include <vector>

#include "igvMaterial.h"
#include "igvFuenteLuz.h"

class TAPJoint {

	TAPMesh mesh;
	std::vector<int> children;
	std::vector<TAPJoint*> joints;

	int rotationLimit1;
	int rotationLimit2;

	int rotacion;

	float R, G, B;

	int x = 0, y = 0, z = 0;

public:
	char rotationAxis;

	TAPJoint() {};
	TAPJoint(TAPMesh _mesh, std::vector<int> _children, char _axis, int r1, int r2, float r, float g, float b) {
		mesh = _mesh;
		children = _children;
		rotationAxis = _axis;
		rotationLimit1 = r1;
		rotationLimit2 = r2;
		rotacion = 0;
		R = r;
		G = g;
		B = b;
		if (rotationAxis == 'X')x++;
		if (rotationAxis == 'Y')y++;
		if (rotationAxis == 'Z')z++;
	};

	void setJoints(std::vector<TAPJoint*> _joints) { joints = _joints; }

	bool aplicarRotacion(int i, int r) {
		int rot = rotacion + r;
		if (rot >= rotationLimit2 && rot <= rotationLimit1) {
			rotacion = rot;
			mesh.rotar(i,i, x, y, z, rotacion);
			for (int j = 0; j < children.size(); j++) {
				joints[children[j]]->aplicarRotacionPadre(i, children[j], x, y, z, rotacion);
			}
			return true;
		}
		else {
			mesh.rotar(i, i, x, y, z, rotacion);
			for (int j = 0; j < children.size(); j++) {
				joints[children[j]]->aplicarRotacionPadre(i, children[j], x, y, z, rotacion);
			}
			return false;
		}
	}

	void resetarRotacion() {
		rotacion = 0;
	}

	void aplicarRotacionPadre(int i,int j, int _x, int _y, int _z, int r) {
		mesh.rotar(i, j, _x, _y, _z, r);
		for (int j = 0; j < children.size(); j++) {
			joints[children[j]]->aplicarRotacionPadre(i, children[j], _x, _y, _z, r);
		}
	}

	void aplicarTraslacion(float _x, float _y, float _z) {
		mesh.trasladar(_x, _y, _z);
		for (int j = 0; j < children.size(); j++) {
			std::cout << children[j] << std::endl;
			joints[children[j]]->aplicarTraslacionPadre(_x, _y, _z);
		}
	}

	void aplicarTraslacionPadre(float _x, float _y, float _z) {
		mesh.trasladar(_x, _y, _z);
	}

	void desaplicartranslacion() {
		mesh.desaplicartranslacion();
		for (int j = 0; j < children.size(); j++) {
			std::cout << children[j] << std::endl;
			joints[children[j]]->desaplicartranslacion();
		}
	}

	/**
	* Funcion encargada de pintar la malla
	*/

	void drawObjectC(int i) {
		mesh.drawObjectC(i);
	};

	~TAPJoint() {};
};

class TAPHumanoid {

	std::vector<TAPJoint> joints;
	int rootJoint;

	igvFuenteLuz luz;
	igvFuenteLuz luz2;
	igvFuenteLuz luz3;
	igvMaterial material;

	bool bbrazos;
	bool bpiernas;

	int piernas;
	int brazos;

	bool andar;
	bool saltar;

public:

	/**
	* Constructores
	*/

	TAPHumanoid() {};
	TAPHumanoid(std::string object, std::string skeleton);

	/**
	* Funcion encargada de pintar la malla
	*/

	void drawObjectC();

	void activatSaltar() {
		joints[0].resetarRotacion();
		joints[1].resetarRotacion();
		joints[2].resetarRotacion();
		joints[3].resetarRotacion();
		joints[4].resetarRotacion();
		joints[5].resetarRotacion();
		joints[6].resetarRotacion();
		joints[7].resetarRotacion();
		joints[8].resetarRotacion();
		joints[9].resetarRotacion();
		joints[10].resetarRotacion();
		joints[11].resetarRotacion();
		joints[12].resetarRotacion();
		joints[13].resetarRotacion();
		joints[14].resetarRotacion();
		saltar = true;
		andar = false;
		piernas = 20;
		brazos = 20;
		bbrazos = true;
		bpiernas = true;
	}

	void activatAndar() {
		joints[0].resetarRotacion();
		joints[1].resetarRotacion();
		joints[2].resetarRotacion();
		joints[3].resetarRotacion();
		joints[4].resetarRotacion();
		joints[5].resetarRotacion();
		joints[6].resetarRotacion();
		joints[7].resetarRotacion();
		joints[8].resetarRotacion();
		joints[9].resetarRotacion();
		joints[10].resetarRotacion();
		joints[11].resetarRotacion();
		joints[12].resetarRotacion();
		joints[13].resetarRotacion();
		joints[14].resetarRotacion();
		saltar = false;
		andar = true;
		piernas = 20;
		brazos = 20;
		bbrazos = true;
		bpiernas = true;
	}

	~TAPHumanoid();
};

