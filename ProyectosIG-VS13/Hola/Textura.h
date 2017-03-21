#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "PixMap24RGB.h"
#include "TextureLoader.h"

class Textura {
public:
	Textura() : w(0), h(0), id(0) {};
	~Textura() { glDeleteTextures(1, &id); };
	void init() {
		glGenTextures(1, &id);
			// generar un nombre

		//unsigned char * data = loadBMPRaw("ray.bmp", w, h, false);
		activar();
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//delete[] data;
	};
		// establecer filtros 
	void activar() { 
		glBindTexture(GL_TEXTURE_2D, id);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	};
	void desactivar() {
		glBindTexture(GL_TEXTURE_2D,0);
		};
	bool load(const std::string & BMP_Name);
	// cargar y transferir a openGL
	void save(const std::string & BMP_Name);
	// obtener de openGL y guardar
public:
	GLuint w, h;
	// dimensiones de la imagen
	GLuint id;
	// identificador interno de la textura
};