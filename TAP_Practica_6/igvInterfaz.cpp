#include <cstdlib>
#include <stdio.h>

#include <glui.h>

#include "igvInterfaz.h"
#include "TAPMesh.h"

#include <windows.h>


extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
							 // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {
	//inicializaci�n de los atributos para realizar la selecci�n mediante lista de impactos
	modo = IGV_VISUALIZAR;

	ang = 70;

	va.set(0, 1.0, 0);

	i = 0;

	tc = 0.5;
	d0 = 8;

	vistas[0].set(6.0, 4.0, d0);
	vistas[1].set(10, 0, 0);
	vistas[2].set(0, 10, 0);
	vistas[3].set(0, 0, d0 + 2);

	planos[1] = -3;
	planos[2] = 1;

	formato = false;
	vista = false;

	animacion = false;

	option = 1;

	// PRACTICA 2
	linearInterpolation = TAPLinearInterpolation("linearInterpolation.txt");
	pt = linearInterpolation.getPrimeraT();
	ut = linearInterpolation.getUltimoT();
	puntoActual = linearInterpolation.getPosicionInterpolada(pt);

	sphericalInterpolation = TAPSphericalInterpolation("sphericalInterpolation.txt");
	spt = sphericalInterpolation.getPrimeraT();
	sut = sphericalInterpolation.getUltimoT();

	travelling = 0;

	pt2 = 0.0f;

	bezier = TAPBezier("bezier.txt");

	velocidad = TAPSpeedController(0.2f, 0.5f);

	movController = TAPMotionController(3000, bezier, velocidad);

	twist = 0.0f;

	//sphericalInterpolation = TAPSphericalInterpolation("sphericalInterpolation.txt");

	pintarBezier = true;

	anaglifo = true;

	vader = TAPHumanoid("vader.obj", "vaderskeleton.txt");

	sistemaparticulas = TAPParticleSystem();
}

igvInterfaz::~igvInterfaz() {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
	//establecer los par�metros de la c�mara en funci�n de la escena concreta que se est� modelando
	interfaz.camara.set(IGV_PARALELA, interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(),
		-1 * 20, 1 * 20, -1 * 20, 1 * 20, interfaz.planos[1], 2000, interfaz.tc);

}

void igvInterfaz::configura_entorno(int argc, char** argv,
	int _ancho_ventana, int _alto_ventana,
	int _pos_X, int _pos_Y, string _titulo) {

	// inicializaci�n de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicializaci�n de la ventana de visualizaci�n
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_ancho_ventana, _alto_ventana);
	glutInitWindowPosition(_pos_X, _pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
	glClearColor(0, 0, 0, 1.0); // establece el color de fondo de la ventana

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
	glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion


	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		// incluir aqu� el cambio de la c�mara para mostrar las vistas planta, perfil, alzado o perspectiva
	case 'V':
	case 'v':
		interfaz.i++;
		interfaz.vistas[3].set(0, 0, 10);
		if (interfaz.i > 3)interfaz.i = 0;
		if (interfaz.i == 2)interfaz.set_va(1.0, 0, 0);
		else interfaz.set_va(0, 1.0, 0);
		interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(), interfaz.tc);
		interfaz.camara.aplicar(0);
		interfaz.camara.aplicar(1);
		break;
	case '1':
		interfaz.opcion = '1';
		std::cout << "K1" << std::endl;
		break;
	case '2':
		interfaz.opcion = '2';
		std::cout << "K2" << std::endl;
		break;
	case '3':
		glClearColor(0, 0, 0, 1.0);
		interfaz.option = 1;
		break;
	case '4':
		glClearColor(0, 0, 0, 1.0);
		interfaz.option = 3;
		break;
	case '5':
		glClearColor(0.5, 0.5, 0.5, 1.0);
		interfaz.option = 2;
		break;
	case '+':
		if (interfaz.opcion == '1' && !interfaz.animacion) {
			interfaz.movController.set_K1(0.05);
			interfaz.velocidad.set_K1(0.05);
		}
		if (interfaz.opcion == '2' && !interfaz.animacion) {
			interfaz.movController.set_K2(0.05);
			interfaz.velocidad.set_K2(0.05);
		}
		break;
	case '-':
		if (interfaz.opcion == '1' && !interfaz.animacion) {
			interfaz.movController.set_K1(-0.05);
			interfaz.velocidad.set_K1(-0.05);
		}
		if (interfaz.opcion == '2' && !interfaz.animacion) {
			interfaz.movController.set_K2(-0.05);
			interfaz.velocidad.set_K2(-0.05);
		}
		break;
	case 't':
		interfaz.escena.setTwist(0.01);
		break;
	case 'T':
		interfaz.escena.setTwist(-0.01);
		break;
	case 'R':
	case 'r':
		interfaz.escena.setTapering(interfaz.escena.getTapering() ? false : true);
		break;
		/*case 'X':
			interfaz.tc += 0.5;
			interfaz.camara.set_tc(interfaz.tc);
			interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(), interfaz.tc);
			break;
		case 'x':
			interfaz.tc -= 0.5;
			interfaz.camara.set_tc(interfaz.tc);
			interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(), interfaz.tc);
			break;
		case 'Z':
			interfaz.d0 += 0.5;
			interfaz.vistas[0].set(6.0, 4.0, interfaz.d0);
			interfaz.vistas[3].set(0, 0, interfaz.d0 + 2);
			interfaz.camara.set_d0(interfaz.d0);
			interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(), interfaz.tc);
			break;
		case 'z':
			interfaz.d0 -= 0.5;
			interfaz.vistas[0].set(6.0, 4.0, interfaz.d0);
			interfaz.vistas[3].set(0, 0, interfaz.d0 + 2);
			interfaz.camara.set_d0(interfaz.d0);
			interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(), interfaz.tc);
			break;*/
	case 'A':
	case 'a': // activa/desactiva la animaci�n de la escena
	// incluir aqu� la activaci�n de la animaci�n
		interfaz.animacion = (interfaz.animacion ? false : true);
		break;
	case 'B':
	case 'b':
		interfaz.pintarBezier = (interfaz.pintarBezier ? false : true);
		break;
	case 'W':
	case 'w':
		interfaz.vader.activatAndar();
		break;
	case 's':
	case 'S':
		interfaz.vader.activatSaltar();
		break;
	case 'e': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);
		break;
	case 27: // tecla de escape para SALIR
		exit(1);
		break;
	}
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::ControlFlechas(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		interfaz.sistemaparticulas.setPosition(-1, 0, 0);
		break;
	case GLUT_KEY_RIGHT:
		interfaz.sistemaparticulas.setPosition(1, 0, 0);
		break;
	case GLUT_KEY_UP:
		interfaz.sistemaparticulas.setPosition(0, 1, 0);
		break;
	case GLUT_KEY_DOWN:
		interfaz.sistemaparticulas.setPosition(0, -1, 0);
		break;
	}

}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
	// dimensiona el viewport al nuevo ancho y alto de la ventana
	// guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

	// establece los par�metros de la c�mara y de la proyecci�n
	interfaz.camara.aplicar(0);
	//interfaz.camara.aplicar(1);
}

void igvInterfaz::set_glutDisplayFunc() {
	GLuint lista_impactos[1024]; // array con la lista de impactos cuando se visualiza en modo selecci�n

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	//for (int i = 0; i < 2; i++) {

	//	glClear(GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());

	//	// se establece el viewport
	//	if (interfaz.anaglifo)glViewport(0, 0, interfaz.get_ancho_ventana() , interfaz.get_alto_ventana());
	//	else {
	//		if (i == 0) {
	//			glViewport(0, 0, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana());
	//		} else {
	//			glViewport(interfaz.get_ancho_ventana() / 2, 0, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana());
	//		}
	//	}

	interfaz.camara.aplicar(0);
	//	// aplica las transformaciones en funci�n de los par�metros de la c�mara y del modo (visualizaci�n o selecci�n)
	//	

	//	if (i == 0) {
	//		interfaz.camara.aplicar(0);
	//		if(interfaz.anaglifo)glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_FALSE);
	//	}
	//	else {
	//		interfaz.camara.aplicar(1);
	//		if (interfaz.anaglifo)glColorMask(GL_FALSE, GL_FALSE, GL_TRUE, GL_FALSE);
	//	}

	//	if (interfaz.pintarBezier)interfaz.bezier.pintarCurva();
	//	else interfaz.velocidad.pintarCurva();

	//	// visualiza la escena
	//	interfaz.escena.visualizar();

	//	if (interfaz.anaglifo)glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	//}

	switch (interfaz.option) {
	case 1:
		interfaz.escena.visualizar();
		break;
	case 2:
		Sleep(50);

		interfaz.vader.drawObjectC();

		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());
		interfaz.camara.aplicar(0);

		interfaz.sistemaparticulas.pintarSistemaPArticulas();
		break;
	case 3:
		if (interfaz.pintarBezier)interfaz.bezier.pintarCurva();
		else interfaz.velocidad.pintarCurva();

		interfaz.escena.visualizar();
		break;
	}

	// refresca la ventana
	glutSwapBuffers();

}

void igvInterfaz::set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y) {
	if (boton == 3) {
		interfaz.camara.zoom(30);
	}
	if (boton == 4) {
		interfaz.camara.zoom(-30);
	}
	if (boton == 1) {
		interfaz.camara.zoom(30);
	}
	glutPostRedisplay();
}

void igvInterfaz::set_glutIdleFunc() {
	// incluir el c�digo para animar el modelo de la manera m�s realista posible
	if (interfaz.animacion) {
		Puntos movimiento;
		Puntos nuevoPunto;
		Quaternion nuevoGiro;

		switch (interfaz.option) {
		case 1:
			/***************************************************************
			*					INTERPOLACION LINEAL					   *
			***************************************************************/
			interfaz.pt += 0.01;
			if (interfaz.pt > interfaz.ut) {
				interfaz.pt = interfaz.linearInterpolation.getPrimeraT();
			}
			nuevoPunto = interfaz.linearInterpolation.getPosicionInterpolada(interfaz.pt);

			movimiento.x = nuevoPunto.x - interfaz.puntoActual.x;
			movimiento.y = nuevoPunto.y - interfaz.puntoActual.y;
			movimiento.z = nuevoPunto.z - interfaz.puntoActual.z;

			/*std::cout << "--------------------------------------------------------" << std::endl;
			std::cout << interfaz.puntoActual.x << " " << interfaz.puntoActual.y << " " << interfaz.puntoActual.z << std::endl;*/

			interfaz.puntoActual = nuevoPunto;

			//std::cout << nuevoPunto.x << " " << nuevoPunto.y << " " << nuevoPunto.z << std::endl;
			//std::cout << movimiento.x << " " << movimiento.y << " " << movimiento.z << std::endl;

			interfaz.escena.setMovimiento(nuevoPunto);

			/***************************************************************
			*					INTERPOLACION ESFERICA					   *
			***************************************************************/
			interfaz.spt += 0.01;
			if (interfaz.spt > interfaz.sut) {
				interfaz.spt = interfaz.sphericalInterpolation.getPrimeraT();
			}
			nuevoGiro = interfaz.sphericalInterpolation.getPosicionInterpolada(interfaz.spt);

			interfaz.escena.setGiro(nuevoGiro);

			glutPostRedisplay();
			break;
		case 2:
			glutPostRedisplay();
			break;
		case 3:
			/***************************************************************
			*		     INTERPOLACION MOVIMIENTO & DEFORMACION			   *
			***************************************************************/

			nuevoPunto = interfaz.movController.get_Punto(interfaz.pt2);

			interfaz.twist = interfaz.movController.get_Twist(interfaz.pt2);

			interfaz.pt2 += 0.01f;
			if (interfaz.pt2 >= 1.0f) {
				interfaz.pt2 = 0.0f;
			}

			/*std::cout << interfaz.pt2 << std::endl;
			std::cout << nuevoPunto.x << " " << nuevoPunto.y << " " << nuevoPunto.z << std::endl;*/

			
			movimiento.x = nuevoPunto.x - interfaz.puntoActual.x;
			movimiento.y = nuevoPunto.y - interfaz.puntoActual.y;
			movimiento.z = nuevoPunto.z - interfaz.puntoActual.z;

			/*std::cout << "--------------------------------------------------------" << std::endl;
			std::cout << interfaz.puntoActual.x << " " << interfaz.puntoActual.y << " " << interfaz.puntoActual.z << std::endl;*/

			interfaz.puntoActual = nuevoPunto;

			//std::cout << nuevoPunto.x << " " << nuevoPunto.y << " " << nuevoPunto.z << std::endl;
			//std::cout << movimiento.x << " " << movimiento.y << " " << movimiento.z << std::endl;

			//std::cout << interfaz.twist << std::endl;

			interfaz.escena.setMovimiento(nuevoPunto);
			interfaz.escena.setTwist(interfaz.twist * 0.7f);

			nuevoGiro = interfaz.sphericalInterpolation.getPosicionInterpolada(interfaz.twist * interfaz.sphericalInterpolation.getUltimoT());

			interfaz.escena.setGiro(nuevoGiro);

			glutPostRedisplay();
			break;

		}
	}
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutIdleFunc(set_glutIdleFunc);
	glutMouseFunc(set_glutMouseFunc);
	glutSpecialFunc(ControlFlechas);
}
