#pragma once

#include "TAPLinearInterpolation.h"

#include <iostream>
#include <string>


class TAPBezier{
	
	Puntos A; //Punto principal 1
	Puntos C0; //Punto de control 1
	Puntos C1; //Punto de control 2
	Puntos B; //Punto principal 2

public:
	TAPBezier();
	TAPBezier(Puntos _a, Puntos _c0, Puntos _c1, Puntos _b);
	TAPBezier(std::string ficheroTXT);
	TAPBezier(const TAPBezier &bezier);

	Puntos getPunto(float _u);

	float distancia(float u1, float u2);

	void pintarCurva();

	void setA(Puntos _a) { A = _a; }
	void setC0(Puntos _c0) { C0 = _c0; }
	void setC1(Puntos _c1) { C1 = _c1; }
	void setB(Puntos _b) { B = _b; }

	~TAPBezier();
};

