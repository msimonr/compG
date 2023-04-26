#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <vector>
#include <list>
#include <cmath>

using namespace std;

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

	glMatrixMode(GL_PROJECTION);

	float color = 0.1;
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
	z = 0;
	float degrees = 0;
	int fps = 60;
	int delay = 1000 / fps;
	float hz = 1 / 5.f;

	//LOOP PRINCIPAL
	int idDp;
	float r;
	float g;
	float b;



	
	do{
		int tick = SDL_GetTicks();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(x, y, z, // pos camara
			0, 0, 0, //punto al que mira la camara
			0, 1, 0); // dirección arriba
		glPushMatrix();

		//TRANSFORMACIONES LINEALES


		//DIBUJAR OBJETOS



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
					glClearColor(0.5, 0.5, 0, 1);
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
