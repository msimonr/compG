#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>

using namespace std;

int main(int argc, char *argv[]) {
	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("Práctico 1",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);

	glMatrixMode(GL_PROJECTION);

	float color = 0;
	glClearColor(color, color, color, 1);
	float aspectRatio = 640 / 480.f;
	gluPerspective(45, aspectRatio, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	bool fin = false;
	bool rotate = false;
	bool fullSize = false;

	SDL_Event evento;

	float x, y, z;

	x = 0;
	y = 0;
	z = 7;
	float degrees = 0;

	//Textura

	char* file = new char[20];
	file = "../../opengl.png";

	//Cargar imagen
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(file);
	FIBITMAP* bitmap = FreeImage_Load(fif, file);
	bitmap = FreeImage_ConvertTo24Bits(bitmap);
	int w = FreeImage_GetWidth(bitmap);
	int h = FreeImage_GetHeight(bitmap);
	void* datos = FreeImage_GetBits(bitmap);
	//Fin carga imagen

	GLuint textura;
	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, datos);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//FIN TEXTURA

	float tam = 0.5;
	float ApTextura = 452 / 212.f;

	//LOOP PRINCIPAL
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		//gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);


		glPushMatrix();
		//TRANSFORMACIONES LINEALES

		//DIBUJAR OBJETOS
		glTranslatef(-1.5, 0, -6);
		
		glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0.0);
			glVertex3f(0, 1, 0);
			glColor3f(0, 1, 0.0);
			glVertex3f(-1, -1., 0);
			glColor3f(0, 0, 1);
			glVertex3f(1, -1, 0);
		glEnd();


		glLoadIdentity();
		glTranslatef(-1.5, 0, -6);
		glTranslatef(3, 0, 0);
		glScaled(tam * ApTextura, tam, 0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textura);

		glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glTexCoord2f(0.095, 0.9);
			glVertex3f(-1, 1, 0);
			glTexCoord2f(0.978, 0.9);
			glVertex3f(1, 1, 0);
			glTexCoord2f(0.978, 0.486);
			glVertex3f(1, -1, 0);
			glTexCoord2f(0.095, 0.486); // 
			glVertex3f(-1, -1, 0);
		glEnd();

		glDisable(GL_TEXTURE_2D);

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
				case SDLK_l:
					glClearColor(0.5, 0.5, 0, 1);
					break;
				case SDLK_RIGHT:
					color += 0.1;
					glClearColor(color, color, color, 1);
					break;
				case SDLK_LEFT:
					color -= 0.1;
					glClearColor(color, color, color, 1);
					break;
				case SDLK_DOWN:
					tam -= 0.015;			
					break;
				case SDLK_UP:
					tam += 0.015;
					break;
				case SDLK_F11:
					if (!fullSize) {
						fullSize = true;
						SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();
						gluPerspective(45, 640 / 480.f, 0.1, 100);
						glMatrixMode(GL_MODELVIEW);
						glLoadIdentity();
					}
					else {
						fullSize = false;
						SDL_SetWindowFullscreen(win, 0);
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();
						gluPerspective(45, 640 / 480.f, 0.1, 100);
						glMatrixMode(GL_MODELVIEW);
						glLoadIdentity();
					}
					break;
				}
			}
		}
		//FIN MANEJO DE EVENTOS
		SDL_GL_SwapWindow(win);
	} while (!fin);
	//FIN LOOP PRINCIPAL
	// LIMPIEZA
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
