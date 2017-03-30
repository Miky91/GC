#include "Textura.h"
#include "tipos.h"

bool Textura::load(const std::string & BMP_Name) {
	// la textura debe estar inicializada -> escena::init()
	try{
		PixMap24RGB pixMap;
		pixMap.load_bmpBGR(BMP_Name);
		// cargar
		// carga correcta??
		w = pixMap.width();
		h = pixMap.height();
		//glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixMap.map());
	}
	catch (int e){
		return false;

	}			// transferir a openGL
	return true;
}

bool Textura::load(const std::string	&BMP_Name, GLubyte	alpha)
{
	// la textura debe estar inicializada -> escena::init()
	try{
		PixMap24RGB pixMap;
		pixMap.load_bmpBGR(BMP_Name);
		// cargar
		// carga correcta??
		w = pixMap.width();
		h = pixMap.height();
		//glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixMap.create_RGBA(alpha));
	}
	catch (int e){
		return false;

	}			// transferir a openGL
	return true;
}
bool Textura::load(const std::string	&BMP_Name, PixMap24RGB::rgb_color	colorKey, GLubyte	alpha)
{
	// la textura debe estar inicializada -> escena::init()
	try{
		PixMap24RGB pixMap;
		pixMap.load_bmpBGR(BMP_Name);
		// cargar
		// carga correcta??
		w = pixMap.width();
		h = pixMap.height();
		//glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixMap.create_RGBA(colorKey, alpha));
	}
	catch (int e){
		return false;

	}			// transferir a openGL
	return true;
}

void Textura::save(const std::string & BMP_Name) {
	//glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB,/*obtener de openGL*/GL_UNSIGNED_BYTE, pA);
	// pA-> array donde guardar los datos (de tipo y tamaño adecuado)
	//...
	// y guardar
	try{
		glReadBuffer(GL_FRONT);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 800, 600, 0);
		PixMap24RGB pixMap;
		pixMap.create_pixmap(800, 600);
		// cargar
		// carga correcta??
		//glBindTexture(GL_TEXTURE_2D, id);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB,/*obtener de openGL*/GL_UNSIGNED_BYTE, pixMap.data());
		pixMap.save_bmpBGR(BMP_Name);
		glReadBuffer(GL_BACK);
	}
	catch (int e){

	}			// transferir a openGL
	
}