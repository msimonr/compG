#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>
#include "tinyxml2.h"


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <vector>
#include <list>
#include <cmath>


using namespace std;
using namespace tinyxml2;

float** cargarCoordXML(char* ruta);

int main(int argc, char *argv[]) {
	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("Practico 1",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);



	//Cargar Textura FONDO (forest-dark1.png)
	char* ruta1 = new char[40];
	ruta1 = "../../practico3/forest-dark1.png";
	FREE_IMAGE_FORMAT fif1 = FreeImage_GetFIFFromFilename(ruta1);
	FIBITMAP* bitmap1 = FreeImage_Load(fif1, ruta1);
	bitmap1 = FreeImage_ConvertTo24Bits(bitmap1);
	int w1 = FreeImage_GetWidth(bitmap1);
	int h1 = FreeImage_GetHeight(bitmap1);
	void* datos1 = FreeImage_GetBits(bitmap1);


	GLuint textura1;
	glGenTextures(1, &textura1);
	glBindTexture(GL_TEXTURE_2D, textura1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w1, h1, 0, GL_BGR, GL_UNSIGNED_BYTE, datos1);
	//fin cargado de textura 1.


	//Cargar Textura FONDO (forest-dark2.png)
	char* ruta2 = new char[40];
	ruta2 = "../../practico3/forest-dark2.png";
	FREE_IMAGE_FORMAT fif2 = FreeImage_GetFIFFromFilename(ruta2);
	FIBITMAP* bitmap2 = FreeImage_Load(fif2, ruta2);
	bitmap2 = FreeImage_ConvertTo32Bits(bitmap2);
	int w2 = FreeImage_GetWidth(bitmap2);
	int h2 = FreeImage_GetHeight(bitmap2);
	void* datos2 = FreeImage_GetBits(bitmap2);



	GLuint textura2;
	glGenTextures(1, &textura2);
	glBindTexture(GL_TEXTURE_2D, textura2);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w2, h2, 0, GL_BGRA, GL_UNSIGNED_BYTE, datos2);
	//fin cargado de textura 2.

	//Cargar Textura FONDO (forest-dark5.png)
	char* ruta3 = new char[40];
	ruta3 = "../../practico3/forest-dark5.png";
	FREE_IMAGE_FORMAT fif3 = FreeImage_GetFIFFromFilename(ruta3);
	FIBITMAP* bitmap3 = FreeImage_Load(fif3, ruta3);
	bitmap3 = FreeImage_ConvertTo32Bits(bitmap3);
	int w3 = FreeImage_GetWidth(bitmap3);
	int h3 = FreeImage_GetHeight(bitmap3);
	void* datos3 = FreeImage_GetBits(bitmap3);

	GLuint textura3;
	glGenTextures(1, &textura3);
	glBindTexture(GL_TEXTURE_2D, textura3);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w3, h3, 0, GL_BGRA, GL_UNSIGNED_BYTE, datos3);
	//fin cargado de textura 3.

	//Cargar Textura FONDO (forest-dark5.png)
	char* ruta4 = new char[50];
	ruta4 = "../../practico3/frogatto-spritesheet1.png";
	FREE_IMAGE_FORMAT fif4 = FreeImage_GetFIFFromFilename(ruta4);
	FIBITMAP* bitmap4 = FreeImage_Load(fif4, ruta4);
	bitmap4 = FreeImage_ConvertTo32Bits(bitmap4);
	int w4 = FreeImage_GetWidth(bitmap4);
	int h4 = FreeImage_GetHeight(bitmap4);
	void* datos4 = FreeImage_GetBits(bitmap4);

	GLuint textura4;
	glGenTextures(1, &textura4);
	glBindTexture(GL_TEXTURE_2D, textura4);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w4, h4, 0, GL_BGRA, GL_UNSIGNED_BYTE, datos4);
	//fin cargado de textura 4.





	glMatrixMode(GL_PROJECTION);

	float color = 0.5f;
	float aspectRatio = 640 / 480.f;

	glClearColor(color, color, color, 1);

	glOrtho(
		0.0f,	//comienzo de las X
		640,	// fin de las X (ancho de ventana)
		480,	//Fin de las Y (empiezan en la esquina superior izquierda)
		0.0f,	// comienzo de las Y
		0.0f,	// comienzo de las Z
		1.0f	// fin de las Z. (si algo cae fuera de [0,1] en Z se corta.
	);	
	glMatrixMode(GL_MODELVIEW);

	bool fin = false;

	SDL_Event evento;

	//Var camara
	float x, y, z;
	x = 0;
	y = 0;
	z = 1;

	//Controlar FPS
	int fps = 60;
	int delay = 1000 / fps;
	float hz = 1 / 1.f;
	float degrees = 0;
	float move = 1;

	char* url = new char[40];
	url = "../../practico3/sprites.xml";

	float** coords;
	coords = cargarCoordXML(url);
	int frame = 0;

	//LOOP PRINCIPAL
	
	do{
	
		int tick = SDL_GetTicks();
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		gluLookAt(x, y, z, // pos camara
			0, 0, 0, //punto al que mira la camara
			0, 1, 0); // dirección arriba

		glPushMatrix();

		//TRANSFORMACIONES LINEALES


		//DIBUJAR OBJETOS
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textura1);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glScalef(1.9, 1.9, 1);
		glBegin(GL_QUADS);
			glColor3f(0.5, 0, 0);
			glTexCoord2f(640/256.f - move, 1);
			glVertex3f(0, 0, 0);
			glTexCoord2f(640/256.f - move, 0);
			glVertex3f(0, h1, 0);
			glTexCoord2f(-move, 0);
			glVertex3f(640, h1, 0);
			glTexCoord2f(-move, 1);
			glVertex3f(640, 0, 0);
		glEnd();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, textura2);

		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glTexCoord2f(640 / 256.f - move*1.5, 1);
		glVertex3f(0, 0, 0.1);
		glTexCoord2f(640 / 256.f - move*1.5, 0);
		glVertex3f(0, h2, 0.1);
		glTexCoord2f(-move*1.5, 0);
		glVertex3f(640, h2, 0.1);
		glTexCoord2f(-move*1.5, 1);
		glVertex3f(640, 0, 0.1);
		glEnd();

		glPopMatrix();

		glPushMatrix();
		glTranslatef(290, 300, 0);
		glScalef(2, 2, 0);
		glBindTexture(GL_TEXTURE_2D, textura4);
		frame = int(degrees) % 8;
		float topY = (h4 - coords[frame][1]) / 512.f;
		float botY = (h4 - coords[frame][1] - coords[frame][3]) / 512.f;
		float minX = (coords[frame][0]) / 512.f;
		float maxX = (coords[frame][0] + coords[frame][2]) / 512.f;

		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);

		glTexCoord2f(minX, topY);
		glVertex3f(0, 0, 0.2);

		glTexCoord2f(minX, botY);
		glVertex3f(0, coords[0][3], 0.2);

		glTexCoord2f(maxX, botY);
		glVertex3f(coords[0][2], coords[0][3], 0.2);

		glTexCoord2f(maxX, topY);
		glVertex3f(coords[0][2], 0, 0.2);

		glEnd();

		glPopMatrix();


		glScalef(1.9, 1.9, 1);
		glBindTexture(GL_TEXTURE_2D, textura3);
		glTranslatef(0, h3*1.1, 0);
		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glTexCoord2f(640 / 256.f -move*2, 1);
		glVertex3f(0, 0, 0.4);
		glTexCoord2f(640 / 256.f -move*2, 0);
		glVertex3f(0, h3, 0.4);
		glTexCoord2f(-move * 2, 0);
		glVertex3f(640, h3, 0.4);
		glTexCoord2f(-move * 2, 1);
		glVertex3f(640,0, 0.4);
		glEnd();

	

		
		glDisable(GL_BLEND);

		glDisable(GL_TEXTURE_2D);

		move += 0.001;
		degrees += 7 * hz / fps;
		frame;

		//FIN DIBUJAR OBJETOS

		//MANEJO DE EVENTOS
		while (SDL_PollEvent(&evento)){
			switch (evento.type) {
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_QUIT:
				fin = true;
				break;
			case SDL_KEYDOWN:
				switch (evento.key.keysym.sym) {
				case SDLK_ESCAPE:
					fin = true;
					break;
				case SDLK_SPACE:
					break;
				case SDLK_l:
					glClearColor(0.5, 0.5, 0.5, 1);
					break;
				case SDLK_UP:				
					break;
				case SDLK_DOWN:
					break;
				case SDLK_RIGHT:			
					break;
				case SDLK_LEFT:
					break;
				case SDLK_F11:
					break;
				}
			}
		}
		//FIN MANEJO DE EVENTOS
		SDL_GL_SwapWindow(win);
		
		
		int delta = SDL_GetTicks() - tick;
		if (delta < delay) {
			SDL_Delay(delay - delta);
		}
	} while (!fin);
	//FIN LOOP PRINCIPAL
	// LIMPIEZA
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

float** cargarCoordXML(char* ruta) {
	//float*
	float** res = new float*[8];
	XMLDocument doc(ruta);
	int error = doc.LoadFile(ruta);
	XMLElement* aux = doc.FirstChildElement("data")->FirstChildElement();
	int i = 0;
	if (error == 0)
		for (XMLElement* elem = aux->FirstChildElement(); elem != nullptr ; elem = elem->NextSiblingElement()) {
			res[i] = new float[4];
			res[i][0] = atof(elem->FindAttribute("x")->Value());
			res[i][1] = atof(elem->FindAttribute("y")->Value());
			res[i][2] = atof(elem->FindAttribute("w")->Value());
			res[i][3] = atof(elem->FindAttribute("h")->Value());	
			i++;
		}
		
	else {
		cout << "Error de carga XML."<<endl;
	}
	return res;
};
/*
<?xml version="1.0"?>
<data>
	<animation animId="walk">
		<frame x="2"   y="110" w="48" h="48" />
		<frame x="53"  y="110" w="48" h="48" />
		<frame x="104" y="110" w="48" h="48" />
		<frame x="155" y="110" w="48" h="48" />
		<frame x="206" y="110" w="48" h="48" />
		<frame x="257" y="110" w="48" h="48" />
		<frame x="308" y="110" w="48" h="48" />
		<frame x="359" y="110" w="48" h="48" />
	</animation>
</data>

*/