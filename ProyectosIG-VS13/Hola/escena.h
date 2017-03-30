//#pragma once
#ifndef _H_escena_H_
#define _H_escena_H_
#include "tipos.h"
#include <vector>
#include "Textura.h"
#include "Math.h"
#define _USE_MATH_DEFINES
#define PI           3.14159265358979323846  /* pi */

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

class Rectangulo
{

public:

	CTex2 textura[4];
	//Color4 color;

	std::vector<PVec3> vertices, normal;
	Rectangulo(double ancho, double alto)
	{
		PVec3 v0(-ancho / 2, alto / 2, 0.0);
		PVec3 v1(-ancho / 2, -alto / 2, 0.0);
		PVec3 v2(ancho / 2, alto / 2, 0.0);
		//PVec3 v3(-ancho / 2, alto / 2, 0.0);
		PVec3 v4(ancho / 2, -alto / 2, 0.0);
		vertices = { v0, v1, v2, v4 };
		GLfloat Qx, Qy, Qz, Px, Py, Pz;

		textura[0] = CTex2(0, 1);
		textura[1] = CTex2(0, 0);
		textura[2] = CTex2(1, 1);
		textura[3] = CTex2(1, 0);
		//color = Color4(1.0, 0.0, 0.0, 1.0);

		PVec3 n(0, 0, 1);
		normal = { n };
		//init();

	}
	void set();
	void draw();
	void activar();
	void desactivar();

private:
	GLuint textureID;
	void init();
	void update();

};



//-------------------------------------------------------------------------

class Triangulo {
public:
	GLuint numDat;
	std::vector<PVec3> vertices, normales;
	int orientacion;
	CTex2 textura[3];
	int r; //radio 
	//GLdouble radGiro = 100;
	GLdouble rotacionZ = 0;
	GLdouble rotacionCentro = 0;

	Triangulo(int radio) {
		r = radio;
		numDat = 3;
		PVec3 v0(radio, 0.0, 0.0);
		PVec3 v1(radio * cos(2 * PI / 3), radio * sin(2 * PI / 3), 0.0);
		PVec3 v2(radio * cos(2 * PI / 3), -radio * sin(2 * PI / 3), 0.0);
		vertices = { v0, v1, v2 };
		
		orientacion = (0 <=(v0.x - v2.x)*(v1.y - v2.y) - (v0.y - v2.y)*(v1.x - v2.x)) ? 1 : -1;
		//(A1.x - A3.x) * (A2.y - A3.y) - (A1.y - A3.y) * (A2.x - A3.x)
		GLdouble Cx, Cy;//Coordenadas del centro del triangulo. Preguntar si harían falta

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
		textura[0] = CTex2(0, 0);
		textura[1] = CTex2(0.5,1);
		textura[2] = CTex2(1, 0);
	}

	~Triangulo() { numDat = 0; }

	//bool load(char arch[]); //genera los datos
	void draw(std::string s);
	void redraw(GLdouble x, GLdouble y);
	bool dentro(GLdouble x, GLdouble y);
	void posicionar(GLdouble x, GLdouble y);
	void rotar();
	void coordTextura(Rectangulo r);
protected:
	void activar();
	void desactivar();
};

//------------------------Piramide----------------------------------------------

class PiramideTri{
	
public:
	Triangulo t,t2,t3;
	GLdouble rotX, rotY, rotZ;
	int rad;
	double hl;
	PiramideTri(int radBase, double h) : t(radBase),t2(radBase),t3(radBase),rad(radBase), hl(h),rotX(0),rotY(0),rotZ(0) {};

	~PiramideTri() { }

	//bool load(char arch[]); //genera los datos
	void draw();
	void drawDiabolo();
	void update(char c);
	
protected:
	void activar();
	void desactivar();
};



//----------------------------TriAnimado----------------------------------

class TriAnimado
{

public:
	GLdouble rotacionZ;
	GLdouble rotacionCentro;
	GLdouble rad;
	Triangulo triangulo = Triangulo(20);
	TriAnimado(GLdouble angZ, GLdouble centro, GLdouble radio);

	void draw();
	void update();

};


//-------------------------------------------------------------------------

class Escena {
public:
	Escena() : ejes(200),piramidetri(25,30), t(25), trianimado(2.0,2.0,30.0), r(300,300)/*piramidetri(50,10)*/ {};
  ~Escena();
  void init();
  void draw();
  void update(char c);
public:
  enum estados { Collage, Recortar, Animar, Diabolo };
  estados actual = Recortar;
  Ejes ejes;
  PiramideTri piramidetri;
  Triangulo t;
  Rectangulo r;
  Textura tx;
  TriAnimado trianimado;

};




#endif  // _H_escena_H_
