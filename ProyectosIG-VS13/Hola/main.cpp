﻿//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <GL/glut.h>

#include <GL/freeglut.h>

#include "tipos.h"
#include "escena.h"
#include <iostream>
using namespace std;

//-------------------------------------------------------------------------

// Window size
int winWidth = 800, winHeight = 600;
GLdouble x = 0;
GLdouble y = 0;
GLdouble previous_x = 0;
GLdouble previous_y = 0;
// Viewport 
PuertoVista viewPort(0, 0, winWidth, winHeight);
bool tilling = false;
// Camera: Scene visible area size and projection
Camara camera(winWidth, winHeight);

// Scene variables
Escena escena;


//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int px, int py);

//-------------------------------------------------------------------------

void intitGL(){ //OpenGL basic setting

  //glEnable(GL_LIGHTING);
  
  //glEnable(GL_DEPTH_TEST);
  //glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);
  //glEnable(GL_POLYGON_SMOOTH);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //glShadeModel(GL_SMOOTH);

  glClearColor(1.0, 1.0, 1.0, 1.0);  // color de fondo (alpha=1 -> opaco)
    
  // ViewPort
  viewPort.set(viewPort.x, viewPort.y, winWidth, winHeight);  // glViewport(0, 0, WIDTH, HEIGHT);

  // Camera position and orentation
  camera.setEZ(); 
  // Scene visible area and projection  
  camera.setVV();

  // Luz ambiente global
  //GLfloat amb[]={0.25, 0.25, 0.25, 1.0};
  //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
  // Light0  set up
  glEnable(GL_LIGHT0);
  GLfloat LuzDifusa[4] = { 1, 1, 1, 1.0 };
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
  //GLfloat LuzSp[4] = { 1, 1, 1, 1 };
  //glLightfv(GL_LIGHT0, GL_SPECULAR, LuzSp);
  //GLfloat LuzAmbiente[4]={0.3f, 0.3f, 0.3f, 1.0f};
  //glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
  GLfloat posLuz0[4] = { 100.0, 100.0, 100.0, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, posLuz0);

  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';
 }

//-------------------------------------------------------------------------

int main(int argc, char *argv[]){

  cout << "Starting console..." << '\n';

  // Initialization
  glutInitWindowSize(winWidth, winHeight);
  //glutInitWindowPosition (140, 140);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInit(&argc, argv);

  // Window construction
  int win = glutCreateWindow( "Freeglut-project" );  // window's identifier
    
  // Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutSpecialFunc(specialKey);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  // OpenGL basic setting
  intitGL();
  escena.init();
  //Triangulo t(50);
  //t.draw();

  glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ; 
						         // after X-closing the window, continue execution
  glutMainLoop();

  cin.sync();
  cin.get();

  return 0;
}

//-------------------------------------------------------------------------

void display(){
 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  GLuint x, y;
  if (tilling)
  {
	  for(int i = 0; i < 3; i++){
		  for (int j = 0; j < 4; j++){
			  x = viewPort.x;
			  y = viewPort.y;
				  viewPort.set(((j*winWidth) / 4), (((i*winHeight)) / 3), winWidth / 4, winHeight / 3);  //glViewport(0, 0, WIDTH, HEIGHT);
				  escena.draw();
			  }
		  
		  }
	 
  }
  else 
  {
	  viewPort.set(0,0, winWidth, winHeight);
	  escena.draw();
  }
	

  glPopMatrix();
  
  glutSwapBuffers();  //glFlush();
}

//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight){

  winWidth = newWidth;
  winHeight = newHeight;

  // Resize Viewport
  viewPort.set(viewPort.x, viewPort.y, winWidth, winHeight);  //glViewport(0, 0, WIDTH, HEIGHT);

  // Resize Scene Visible Area 
  camera.setVV(winWidth, winHeight);
}

//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y){

  bool need_redisplay = true;

  switch (key) {
  case 27:  // Escape key 
    glutLeaveMainLoop(); // Freeglut's sentence for stopping glut's main loop 
    break;
  case '+':
	  if (escena.actual != escena.Recortar)
		  glScaled(1.1, 1.1, 1.1); // aumentar la escala 
	  else
		  escena.update('+');
	  break;
  case '-':
	  if (escena.actual != escena.Recortar)
		  glScaled(0.9, 0.9, 0.9); // reducir la escala 
	  else
		  escena.update('-');
	  break;
  case 'l':
	  camera.set3D(); 
	  break;
  case 'o':
	  camera.setEZ();
	  break;
  case 't':
	  escena.update('t');
	  break;
  case 'x':
	  if (escena.actual == escena.Diabolo)
		  escena.update('x');
	  break;
  case 'm':
	  tilling = !tilling;
  case 'y':
	  if (escena.actual == escena.Diabolo)
		  escena.update('y');
	  break;
  case '5':
	  escena.actual = escena.Cube;
	  break;
  case 'z':
	  if (escena.actual == escena.Diabolo)
		  escena.update('z');
	  break;
  case 'r':
		  escena.t.rota = true;
		  escena.update('r');
	  break;
  case '2':
//	  escena.load();
	  if (escena.actual == escena.Collage)
		  escena.save();
	  escena.tx = escena.collage;
	  escena.t.vertices = escena.trianimado.triangulo.vertices;
	  escena.actual = escena.Recortar;
	  escena.update(' ');
	  break;
  case '3':

	  escena.t.coordTextura(escena.r);
	  for (int i = 0; i < 3; i++)
	  {
		  escena.trianimado.triangulo.textura[i] = escena.t.textura[i];
	  }
	  escena.actual = escena.Animar;

	  escena.update(' ');
	  break;
  case '4':
	  escena.t.coordTextura(escena.r);
	  for (int i = 0; i < 3; i++)
	  {
		  escena.piramidetri.t.textura[i] = escena.t.textura[i];
		  escena.piramidetri.t2.textura[i] = escena.t.textura[i];
		  escena.piramidetri.t3.textura[i] = escena.t.textura[i];
	  }
	  escena.actual = escena.Diabolo;
	  escena.update(' ');
	  break;
  //case '2':
	//  escena.actual = escena.Collage;
	  //escena.update(' ');
	  break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}

//-------------------------------------------------------------------------

void specialKey(int key, int x, int y){

  bool need_redisplay = true;

  switch (key) {
  case GLUT_KEY_RIGHT:
    glTranslated(1, 0, 0);  // trasladar 1 en el eje X
    break;
  case GLUT_KEY_LEFT:
    glTranslated(-1, 0, 0);
    break;
  case GLUT_KEY_UP:
    glRotated(1, 0, 0, 1);  // girar 1 en el eje Z
    break;
  case GLUT_KEY_DOWN:
    glRotated(-1, 0, 0, 1);
    break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}

//-------------------------------------------------------------------------

void mouse(int button, int state, int px, int py){
	//x = float(px);
	
	//if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) { // DOWN

	PVec3 *data = escena.t.vertices.data();

		cout << data[0].x << endl;
		cout << data[1].x << endl;
		cout << data[2].x << endl;

	//}
}

//-------------------------------------------------------------------------

void motion(int px, int py)
{	
//	escena.t.rota = false;
	px = float(px) - (winWidth / 2);
	py = (winHeight - float(py)) - (winHeight / 2);
	if (escena.t.dentro(px, py))
	{/*
		float j = x - (x - 1);
		float t = y - (y - 1);
		if (x > previous_x)
		{
			previous_x = x;
			j = 3;
		}
		else if (x < previous_x)
		{
			previous_x = x;
			j = -3;
		}
		if (y > previous_y)
		{
			t = 3;
			previous_y = y;
		}

		else if (y < previous_y)
		{
			t = -3;
			previous_y = y;
		}
		
		PVec3 *data = escena.t.vertices.data();
		data[0].x += j;
		data[1].x += j;
		data[2].x += j;
		data[0].y += t;
		data[1].y += t;
		data[2].y += t;*/
		/*PVec3 *data = escena.t.vertices.data();
		data[0].x += data[0].x + x;
		data[1].x += data[1].x + x;
		data[2].x += data[2].x + x;
		data[0].y += data[0].y + y;
		data[1].y += data[1].y + y;
		data[2].y += data[2].y + y;
		*/escena.t.posicionar(px,py);
		//escena.t.recalculaVertices();
		//escena.t.draw("Recortar");//.redraw(x, y);
	}
	glutPostRedisplay();
}



