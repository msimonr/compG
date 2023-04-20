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

	SDL_Window* win = SDL_CreateWindow("Practico 1",
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
	int fps = 60;
	int delay = 1000 / fps;
	//Hz = 1/T
	float hz = 1 / 5.f;

	glLineStipple(4, 0xAAAA);
	glLineWidth(1);

	//LOOP PRINCIPAL
	do{
		int tick = SDL_GetTicks();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		//gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
	

		glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0.5, 0);
		glEnd();
		glBegin(GL_LINES);
			glColor3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0.5, 0, 0);
		glEnd();
		glBegin(GL_LINES);
			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 0.5);
		glEnd();

		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
			glColor3f(1, 1, 1);
			glVertex3f(0, -5, -6);
			glVertex3f(0, 5, -6);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		//TRANSFORMACIONES LINEALES

		//DIBUJAR OBJETOS

		glTranslatef(0, 0, -6);
		glRotatef(degrees, 0, 1, 0);
		glTranslatef(0, 0, 6);

		glPushMatrix();

		glTranslatef(-1.5, 0, -6);
		glRotatef(degrees, 0, 1, 0);

		glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0);
			glVertex3f(0, 1, 0);
			glColor3f(0, 1, 0);
			glVertex3f(-1, -1., 0);
			glColor3f(0, 0, 1);
			glVertex3f(1, -1, 0);
		glEnd();

		glPopMatrix();
		//glTranslatef(0, 0, -6);
		//glRotatef(degrees, 0, 1, 0);
		//glTranslatef(0, 0, 6);
		glTranslatef(3, 0, 0);
		glTranslatef(-1.5, 0, -6);
		glRotatef(degrees, 0, 1, 0);

		glBegin(GL_QUADS);
			glColor3f(0, 1, 1);			
			glVertex3f(-1, 1, 0);			
			glVertex3f(1, 1, 0);			
			glVertex3f(1, -1, 0);
			glVertex3f(-1, -1, 0);
		glEnd();
		
		//FIN DIBUJAR OBJETOS
		degrees += 360*hz/60;

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
					if(color <= 1){
						color += 0.1;
						glClearColor(color, color, color, 1);
					}
					break;
				case SDLK_LEFT:
					if (color >= 0) {
						color -= 0.1;
						glClearColor(color, color, color, 1);
					}
					break;
				case SDLK_DOWN:					
					break;
				case SDLK_UP:				
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
