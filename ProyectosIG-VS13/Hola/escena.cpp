#include "escena.h"
#include <GL/freeglut.h>

//-------------------------------------------------------------------------

void Escena::init(){
	//glEnable(GL_TEXTURE_2D);
	trans.init();
	trans.activar();
	trans.load("Zelda.bmp", 100);
	trans.desactivar();
	smile.init();
	smile.activar();
	smile.load("smile.bmp", PixMap24RGB::rgb_color{255,255,255}, 120);
	smile.desactivar();
	tx.init();
	tx.activar();
	tx.load("ray.bmp");
	tx.desactivar();
  // texturas
  // luces
}

void Escena::update(char c)
{
	
	switch (actual){
	case Animar:
		//glEnable(GL_DEPTH_TEST);
		
		trianimado.update();
		break;
	case Recortar:
		//glDisable(GL_DEPTH_TEST);
		if (c == 'r')
			t.rotar();
		else if ((c == '+') || (c == '-'))
			t.update(c);
		break;
	case Collage:

		break;
	case Diabolo:
		//glEnable(GL_DEPTH_TEST);
		piramidetri.update(c);
		break;
	case Cube:
		cubo.update();
		break;
	}
}

//-------------------------------------------------------------------------

Escena::~Escena(){
   // liberar memoria y recursos 
}

//-------------------------------------------------------------------------

void Escena::save()
{
	collage.init();
	collage.activar();
	collage.save("collage.bmp");
	collage.desactivar();
}
void Escena::load()
{
	collage.init();
	collage.activar();
	collage.load("collage.bmp");
	collage.desactivar();
}

void Escena::draw(){
	if (actual == Animar)
	{
		glEnable(GL_DEPTH_TEST);
		ejes.draw();
		//piramidetri.drawDiabolo();
		collage.activar();
	//	t.draw(" ");
		trianimado.triangulo.vertices = t.vertices;
		trianimado.draw();
		collage.desactivar();
	}
	else if (actual == Diabolo)
	{
		glEnable(GL_DEPTH_TEST);
		ejes.draw();
		collage.activar();
		// glTexParameterf(GL_TEXTURE_2D,);
		//r.draw();
		piramidetri.drawDiabolo();
		collage.desactivar();
	}
	else if (actual == Recortar)
	{

		glEnable(GL_DEPTH_TEST);
		t.recalculaVertices();

		t.draw("Recortar");
		tx.activar();
		r.draw();
		tx.desactivar();	
		
	}
	else if (actual == Collage)
	{
		glDisable(GL_DEPTH_TEST);
		tx.activar();
		r.draw();
		tx.desactivar();
		glPushMatrix();
		trans.activar();
		glTranslated(-80, -70, 0);
		glRotated(-45, 0, 0, 1);
		transRectangulo.draw();
		glTranslated(150, 150, 0);
		translucido.draw("");
		trans.desactivar();
		glPopMatrix();
		smile.activar();
		smileRectangulo.draw();
		smile.desactivar();
		
	}
	else if (actual == Cube)
	{
		ejes.draw();
		glEnable(GL_DEPTH_TEST);
		tx.activar();
		cubo.draw();
		tx.desactivar();
		
		//tx.activar();
		//tx.desactivar();
	}

	
}

//-------------------------------------------------------------------------

Ejes::Ejes(GLdouble l) {
  vertices[0].set(0, 0, 0);
  vertices[1].set(l, 0, 0);
  vertices[2].set(0, 0, 0);
  vertices[3].set(0, l, 0);
  vertices[4].set(0, 0, 0);
  vertices[5].set(0, 0, l);

  colores[0].set(1, 0, 0);
  colores[1].set(1, 0, 0);
  colores[2].set(0, 1, 0);
  colores[3].set(0, 1, 0);
  colores[4].set(0, 0, 1);
  colores[5].set(0, 0, 1);
}

//-------------------------------------------------------------------------

void Ejes::draw(){
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, &vertices[0]);
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_DOUBLE, 0, colores);

  glLineWidth(2);
  glDrawArrays(GL_LINES, 0, 6); 
  glLineWidth(1);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

 /* 
  glLineWidth(2);
  glBegin(GL_LINES);
     glColor3d(1.0, 0.0, 0.0); // red
     glVertex3d(vertices[0].x, vertices[0].y, vertices[0].z);   // origin
     glVertex3d(vertices[1].x, vertices[1].y, vertices[1].z);   // x   

     glColor3d(0.0, 1.0, 0.0); // green
     glVertex3d(vertices[2].x, vertices[2].y, vertices[2].z);   // origin
     glVertex3d(vertices[3].x, vertices[3].y, vertices[3].z);	  // y

     glColor3d(0.0, 0.0, 1.0); // blue
     glVertex3d(vertices[4].x, vertices[4].y, vertices[4].z);   // origin
     glVertex3d(vertices[5].x, vertices[5].y, vertices[5].z);	  // z   
  glEnd();
  glLineWidth(1);
  */
}

//-------------------------------------------------------------------------
void Triangulo::draw( std::string s)
{
	glEnable(GL_BLEND);
	glPushMatrix();
	activar();
	glColor4d(255, 255, 255, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glScaled(scaled, scaled, scaled);
	glNormal3d(normales[0].x, normales[0].y, normales[0].z);
	if (s == "Recortar")
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, numDat);
	desactivar();
	glPopMatrix();
	glDisable(GL_BLEND);
	//----
	

}
void Triangulo::update(char c)
{
	if (c == '+')
		scaled += 0.1;
	else if (c == '-')
		scaled -= 0.1;
	recalculaVertices();

}
void Triangulo::recalculaVertices()
{
	PVec3 *data = vertices.data();
	for (int i = 0; i < 3; i++)
	{
//		angulos[i] += (rotacion/10)*(PI / 18);
		data[i].x = x+r*scaled*cos(angulos[i]);
		data[i].y = y+r*scaled*sin(angulos[i]);
	}

}



void Triangulo::coordTextura(Rectangulo r)
{
	GLdouble porcX;
	GLdouble porcY;
	PVec3 *arr = r.vertices.data();
	PVec3 *var = vertices.data();
	porcX = (arr[2].x + var[0].x) / (arr[2].x * 2);
	porcY = (arr[2].y + var[0].y) / (2 * arr[2].y);
	textura[0] = CTex2(porcX, porcY);
	porcX = (arr[2].x + var[1].x) / (2 * arr[2].x);
	porcY = (arr[2].y + var[1].y) / (2 * arr[2].y);
	textura[1] = CTex2(porcX, porcY);
	porcX = (arr[2].x + var[2].x) / (2 * arr[2].x);
	porcY = (arr[2].y + var[2].y) / (2 * arr[2].y);
	textura[2] = CTex2(porcX, porcY);

}

void Triangulo::activar() {
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glNormalPointer(GL_DOUBLE, 0, normales.data());
	glVertexPointer(3, GL_DOUBLE, 0, &vertices[0]);
	glTexCoordPointer(2, GL_DOUBLE, 0, textura);


}

void Triangulo::desactivar() {
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

bool Triangulo::dentro(GLdouble x, GLdouble y)
{
	PVec3 *v = vertices.data();
	bool cond = true;
	return cond = (((orientacion >= 0) &&
		((v[2].x - x)*(v[0].y - y) - (v[2].y - y)*(v[0].x - x) >= 0) &&
		((v[1].x - x)*(v[2].y - y) - (v[1].y - y)*(v[2].x - x) >= 0) &&
		((v[0].x - x)*(v[1].y - y) - (v[0].y - y)*(v[1].x - x) >= 0))
		|| ((orientacion < 0) &&
		((v[2].x - x)*(v[0].y - y) - (v[2].y - y)*(v[0].x - x) < 0) &&
		((v[1].x - x)*(v[2].y - y) - (v[1].y - y)*(v[2].x - x) < 0) &&
		((v[0].x - x)*(v[1].y - y) - (v[0].y - y)*(v[1].x - x) < 0))) ? true : false;
		

}
void Triangulo::posicionar(GLdouble px, GLdouble py)
{
//	glPushMatrix();
	x = px;
	y = py;
	recalculaVertices();
//	glTranslated(x, y, 0);
	//draw("Recortar");
	//glPopMatrix();
}

void Triangulo::rotar()
{
	for (int i = 0; i < 3; i++)
	{
		angulos[i] += 0.2;
	}
//	angulos[0] += 10;

//	redraw(x,y);
	//glPushMatrix();
	//glTranslated(-x, -y, 0);
	//glRotated(rotacion, 0, 0, 1);
	//glTranslated(x, y, 0);
	//glTranslated(x, y, 0);
	//draw("Recortar");
	//glPopMatrix();
	
}



void PiramideTri::draw()
{
	//glTranslated(0, 25, 0);
	//glRotated(-30, 0, 0, 1);
	PVec3 *aux = t.vertices.data();
	hl = 25;
	aux[0].z = 2 * hl;
	aux[0].y = 0;
	aux[0].x = 0;
	t.vertices[0] = *aux;
	t.draw("");
	aux = t3.vertices.data();
	t2.draw("");
	//aux[2].y = hl;
	aux[1].x = 0;
	aux[1].y = 0;
	aux[1].z = 2 * hl;
	t3.draw("");

	//t.draw();

}
void PiramideTri::update(char c)
{
	if (c == 'x')
		rotX += 2;
	else if (c == 'y')
		rotY += 2;
	else if (c == 'z')
		rotZ += 2;
	/*
	glPushMatrix();
	glRotated(rotacionZ, 0, 0, 1);
	glTranslated(rad, 0, 0);
	glRotated(rotacionCentro, 0, 0, 1);
	triangulo.draw();
	glPopMatrix();

	*/
}

void Rectangulo::draw()
{

	activar();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0, 0, 0, 1);
	PVec3 *data = normal.data();
	glNormal3d(data[0].x, data[0].y, data[0].z);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisable(GL_BLEND);
	desactivar();
}

void Rectangulo::activar() {
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glNormalPointer(GL_DOUBLE, 0, normal.data());
	glVertexPointer(3, GL_DOUBLE, 0, vertices.data());
	glTexCoordPointer(2, GL_DOUBLE, 0, textura);
}

void Rectangulo::desactivar() {
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


}



void PiramideTri::drawDiabolo()
{
	glPushMatrix();
	glRotated(rotX, 1, 0, 0);
	glRotated(rotY, 0, 1, 0);
	glRotated(rotZ, 0, 0, 1);
	glTranslated(0, 2*hl, 0);
	glRotated(90, 1, 0, 0);
	draw();
	glTranslated(0, 0, 4 * hl);
	glRotated(180,1, 0, 0);
	draw();
	glRotated(60, 0, 0, 1);
	draw();
	glTranslated(0, 0, 4 * hl);
	glRotated(180, 1, 0, 0);
	draw();

	glPopMatrix();
}

TriAnimado::TriAnimado(GLdouble angZ, GLdouble centro, GLdouble radio)
{
	rotacionZ = angZ;
	rotacionCentro = centro;
	rad = radio;
}
void TriAnimado::draw()
{
	
	glPushMatrix();
	glRotated(rotacionZ,0,0,1);
	glTranslated(rad,0,0);
	glRotated(rotacionCentro,0,0,1);
	triangulo.draw("");
	glPopMatrix();
//	if (c == 'r')
	//	glRotated(rotacionCentro, 0, 0, 1);

}
void TriAnimado::update()
{
	rotacionZ += 10.0;
}

Cubo::Cubo(double lado)
{
		PVec3 v = PVec3(-lado/2,lado/2, -lado/2);
		PVec3 v1 = PVec3(-lado / 2, -lado/2, -lado / 2);
		PVec3 v2 = PVec3(-lado / 2, lado/2, lado/2);
		PVec3 v3 = PVec3(-lado / 2, -lado / 2, lado / 2);

		PVec3 v4 = PVec3(lado / 2, lado / 2, lado / 2);
		PVec3 v5 = PVec3(lado / 2, -lado / 2, lado / 2);
		PVec3 v6 = PVec3(lado / 2, lado / 2, -lado / 2);
		PVec3 v7 = PVec3(lado / 2, -lado / 2, -lado / 2);

		vertices = { v, v1, v2, v3, v4, v5, v6, v7 };
		PVec3 n(0, 0, 1);
		normal = { n };
		textura[0] = CTex2(0, 1);
		textura[1] = CTex2(0, 0);
		textura[2] = CTex2(1, 1);
		textura[3] = CTex2(1, 0);
		
}

void Cubo::activar()
{
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glNormalPointer(GL_DOUBLE, 0, normal.data());
	glVertexPointer(3, GL_DOUBLE, 0, vertices.data());
//	glTexCoordPointer(2, GL_DOUBLE, 0, textura);
}

void Cubo::desactivar() {
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);


}
Cubo::~Cubo()
{

}

void Cubo::update()
{
	rot += 5;
	scaled += 0.1;
	
}
void Cubo::draw()
{
	glPushMatrix();
	activar();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0, 0, 0, 1);
	PVec3 *data = normal.data();
	glRotated(rot, 0, 0, 1);
	glScaled(scaled, scaled, scaled);
	glNormal3d(data[0].x, data[0].y, data[0].z);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL/*GL_LINE*/);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
	glRotated(90, 0, 0, 1);
	glRotated(180, 1, 0, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
	glDisable(GL_BLEND);
	desactivar();
	glPopMatrix();
}

