//#pragma once
#ifndef _H_escena_H_
#define _H_escena_H_
#include "tipos.h"
#include <vector>
#include "Math.h"
#define _USE_MATH_DEFINES
# define PI           3.14159265358979323846  /* pi */
//-------------------------------------------------------------------------
class Ejes {
public:
  Ejes(GLdouble l);
  ~Ejes(){};
  void draw();
public:
  PVec3 vertices[6];
  PVec3 colores[6];
};

//-------------------------------------------------------------------------

class Triangulo {
public:
	GLuint numDat;
	std::vector<PVec3> vertices, normales;

	Triangulo(int radio) {

		numDat = 3;
		PVec3 v0(radio, 0.0, 0.0);
		PVec3 v1(radio * cos(2 * PI / 3), radio * sin(2 * PI / 3), 0.0);
		PVec3 v2(radio * cos(2 * PI / 3), -radio * sin(2 * PI / 3), 0.0);
		vertices = { v0, v1, v2 };


		/////Normales
		GLfloat Qx, Qy, Qz, Px, Py, Pz;

		Px = v1.x - v0.x;
		Py = v1.y - v0.y;
		Pz = v1.z - v0.z;
		Qx = v2.x - v0.x;
		Qy = v2.y - v0.y;
		Qz = v2.z - v0.z;
		PVec3 NormalX = Py*Qz - Pz*Qy;
		PVec3 NormalY = Pz*Qx - Px*Qz;
		PVec3 NormalZ = Px*Qy - Py*Qx;

		normales = { NormalX, NormalY, NormalZ };
	}

	~Triangulo() { numDat = 0; }

	//bool load(char arch[]); //genera los datos
	void draw();

protected:
	void activar();
	void desactivar();
};

//------------------------Piramide----------------------------------------------

class PiramideTri{
	
public:
	Triangulo t,t2,t3;
	int rad;
	double hl;
	PiramideTri(int radBase, double h) : t(radBase),t2(radBase),t3(radBase),rad(radBase), hl(h) {};

	~PiramideTri() { }

	//bool load(char arch[]); //genera los datos
	void draw();
	void drawDiabolo();
	void rota();
	
protected:
	void activar();
	void desactivar();
};


class Rectangulo
{
	
public:

	//CTex2 textura;
//	Color4 color;
	std::vector<PVec3> vertices, normal;
	Rectangulo(double ancho, double alto)
	{
		PVec3 v0(ancho / 2, -alto / 2, 0.0);
		PVec3 v1(ancho / 2, alto / 2, 0.0);
		PVec3 v2(-ancho / 2, alto / 2, 0.0);
		PVec3 v3(-ancho / 2, alto / 2, 0.0);
		PVec3 v4(-ancho / 2, -alto / 2, 0.0);
		vertices = { v0, v1, v2, v0 , v3, v4};
		GLfloat Qx, Qy, Qz, Px, Py, Pz;

		Px = v1.x - v0.x;
		Py = v1.y - v0.y;
		Pz = v1.z - v0.z;
		Qx = v2.x - v0.x;
		Qy = v2.y - v0.y;
		Qz = v2.z - v0.z;
		PVec3 NormalX = Py*Qz - Pz*Qy;
		PVec3 NormalY = Pz*Qx - Px*Qz;
		PVec3 NormalZ = Px*Qy - Py*Qx;

		normal = { NormalX, NormalY, NormalZ };


	}
	void draw();
	void activar();
	void desactivar();
};

//----------------------------TriAnimado----------------------------------

class TriAnimado : Triangulo
{
	
};


//-------------------------------------------------------------------------

class Escena {
public:
	Escena() : ejes(200), r(10,10)/*piramidetri(50,10)*/ {};
  ~Escena();
  void init();
  void draw();
public:
  Ejes ejes;
  //PiramideTri piramidetri;
  Rectangulo r;
};




#endif  // _H_escena_H_
