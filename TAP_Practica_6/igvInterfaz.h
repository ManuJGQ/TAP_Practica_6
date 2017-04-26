#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#include <glut.h>
#include <string>

#include "igvEscena3D.h"
#include "igvCamara.h"

#include "TAPLinearInterpolation.h"
#include "TAPSphericalInterpolation.h"
#include "TAPMotionController.h"
#include "TAPStereoscopicCamera.h"
#include "TAPHumanoid.h"

#include "TAPParticleSystem.h"

using namespace std;

typedef enum {
	IGV_VISUALIZAR,
	IGV_SELECCIONAR
} modoInterfaz;

class igvInterfaz {
	float pt;
	Punto puntoActual;

	//Humanoide
	TAPHumanoid vader;

	//Bezier
	TAPBezier bezier;

	//Speed
	TAPSpeedController velocidad;

	//Controlador Movimiento
	TAPMotionController movController;

	//Interpolacion Esferica
	TAPSphericalInterpolation sphericalInterpolation;

	//Sistema de Particulas
	TAPParticleSystem sistemaparticulas;

	//Deformacion
	float twist;

	char opcion;

	bool pintarBezier;

protected:
	// Atributos
	int ancho_ventana; // ancho inicial de la ventana de visualizacion
	int alto_ventana;  // alto inicial de la ventana de visualizacion

	igvPunto3D vistas[4];
	igvPunto3D va;

	bool formato;
	bool vista;
	bool perspectiva;

	igvEscena3D escena; // escena que se visualiza en la ventana definida por igvInterfaz
	TAPStereoscopicCamera camara;

	bool anaglifo;

	float tc;
	float d0;

	// atributos para la selecci�n mediante el rat�n
	modoInterfaz modo; // IGV_VISUALIZAR: en la ventana se va a visualizar de manera normal la escena, 
					   // IGV_SELECCIONAR: se ha pulsado sobre la ventana de visualizaci�n, la escena se debe
					   // visualizar en modo selecci�n para el c�lculo de la lista de impactos

public:
	// Constructores por defecto y destructor
	igvInterfaz();
	~igvInterfaz();

	int i;
	int ang;
	double planos[2];

	bool animacion;

	// Metodos est�ticos
	// callbacks de eventos
	static void set_glutKeyboardFunc(unsigned char key, int x, int y); // metodo para control de eventos del teclado
	static void set_glutReshapeFunc(int w, int h); // m�todo que define la camara de vision y el viewport
												   // se llama autom�ticamente cuano se camba el tama�o de la ventana
	static void set_glutDisplayFunc(); // m�todo para visualizar la escena
	static void set_glutIdleFunc(); // m�todo para animar la escena

	static void set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y); //RATON

	// Metodos

	// crea el mundo que se visualiza en la ventana
	void crear_mundo(void);

	// inicializa todos los par�metros para crear una ventana de visualizaci�n
	void configura_entorno(int argc, char** argv, // parametros del main
		int _ancho_ventana, int _alto_ventana, // ancho y alto de la ventana de visualizaci�n
		int _pos_X, int _pos_Y, // posicion inicial de la ventana de visualizaci�n
		string _titulo // t�tulo de la ventan de visualizaci�n
	);
	void inicializa_callbacks(); // inicializa todas los callbacks

	void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

	// m�todos get_ y set_ de acceso a los atributos
	int get_ancho_ventana() { return ancho_ventana; };
	int get_alto_ventana() { return alto_ventana; };

	void set_ancho_ventana(int _ancho_ventana) { ancho_ventana = _ancho_ventana; };
	void set_alto_ventana(int _alto_ventana) { alto_ventana = _alto_ventana; };

	igvPunto3D get_vistas(int i) { return vistas[i]; };
	igvPunto3D get_va() { return va; };
	void set_va(const double& x, const double& y, const double& z) { va.set(x, y, z); };

	bool get_formato() { return formato; };
	void set_formato(bool _formato) { formato = _formato; };
	bool get_vista() { return vista; };
	void set_vista(bool _vista) { vista = _vista; };
	bool get_perspectiva() { return perspectiva; };
	void set_perspectiva(bool _perspectiva) { perspectiva = _perspectiva; };

	bool get_anaglifo() { return anaglifo; };
	void set_anaglifo(bool _anaglifo) { anaglifo = _anaglifo; };

};



#endif
