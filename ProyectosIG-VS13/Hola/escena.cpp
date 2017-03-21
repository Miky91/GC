#include "escena.h"
#include "TextureLoader.h"
#include <GL/freeglut.h>

//-------------------------------------------------------------------------

void Escena::init(){
	glEnable(GL_TEXTURE_2D);
	tx.init();
	tx.load("ray.bmp");
  // texturas
  // luces
}

void Escena::update()
{
	trianimado.update();
}

//-------------------------------------------------------------------------

Escena::~Escena(){
   // liberar memoria y recursos 
}

//-------------------------------------------------------------------------

void Escena::draw(){
  ejes.draw();
  //piramidetri.drawDiabolo();
  trianimado.draw();
  tx.activar();
 // glTexParameterf(GL_TEXTURE_2D,);
  r.draw();
  piramidetri.drawDiabolo();
  tx.desactivar();
  
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
void Triangulo::draw()
{
	activar();
	glColor4d(0, 0, 0, 1);
	glNormal3d(normales[0].x, normales[0].y, normales[0].z);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, numDat);
	desactivar();
	//----
	

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


void PiramideTri::draw()
{
	//glTranslated(0, 25, 0);
	//glRotated(-30, 0, 0, 1);
	PVec3 *aux = t.vertices.data();
	hl = 25;
	aux[0].z = 2*hl;
	aux[0].y = 0;
	aux[0].x = 0;
	t.vertices[0] = *aux;
	t.draw();
	aux = t3.vertices.data();
	t2.draw();
	//aux[2].y = hl;
	aux[1].x = 0;
	aux[1].y = 0;
	aux[1].z = 2*hl;
	t3.draw();

	//t.draw();
	
}

void Rectangulo::draw()
{

	activar();

	//glEnable(GL_TEXTURE_2D);
	glColor4d(0, 0, 0, 1);
	PVec3 *data = normal.data();
	glNormal3d(data[0].x, data[0].y, data[0].z);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
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
	triangulo.draw();
	glPopMatrix();


}
void TriAnimado::update()
{
	rotacionZ += 10.0;
	rotacionCentro += 10.0;
}