#pragma once

#include <vector>

#include "TAPBezier.h"
#include "TAPSpeedController.h"

class TAPMotionController{

	int nEntradasTabla;

	TAPBezier desplazamiento;
	TAPSpeedController velocidad;

	std::vector< std::pair<float,int> > tablaIncrementos;

public:
	TAPMotionController();
	TAPMotionController(int n, TAPBezier _desp, TAPSpeedController _vel);
	TAPMotionController(const TAPMotionController &motioncontroller);

	void construirTablaIncrementos();
	int get_Indice(float s);

	Puntos get_Punto(float t);

	float get_Twist(float t);

	void set_nEntradasTable(int _n) {
		nEntradasTabla = _n;
		construirTablaIncrementos();
	}

	//Sets de la curva de Bezier
	void set_A(Puntos _a) { 
		desplazamiento.setA(_a); 
		construirTablaIncrementos();
	}
	void set_C0(Puntos _c0) { 
		desplazamiento.setC0(_c0); 
		construirTablaIncrementos();
	}
	void set_C1(Puntos _c1) { 
		desplazamiento.setC1(_c1);
		construirTablaIncrementos();
	}
	void set_B(Puntos _b) { 
		desplazamiento.setB(_b);
		construirTablaIncrementos();
	}

	//Sets de la curva de velocidad
	void set_K1(float _k1) { velocidad.set_K1(_k1); }
	void set_K2(float _k2) { velocidad.set_K2(_k2); }

	~TAPMotionController();
};

