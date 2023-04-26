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

string lectura(string path);
vector<float> string2vectorFloat(string lista);
list<vector<float>> cargarVertices(string lista);

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
	//Hz = 1/T
	float hz = 1 / 5.f;
	//LOOP PRINCIPAL
	float camYaw = 0;
	int idDp;
	float r;
	float g;
	float b;



	
	do{
		int tick = SDL_GetTicks();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(x, y, z, // pos camara
			x + sin(camYaw), 0, z-cos(camYaw), //punto al que mira la camara
			0, 1, 0); // dirección arriba
		glPushMatrix();

		//TRANSFORMACIONES LINEALES


		//DIBUJAR OBJETOS

		glBegin(GL_QUADS);
			glColor3f(0, 255, 0);
			glVertex3f(1,1,0);
			glVertex3f(1,-1,0);
			glVertex3f(-1,-1,0);
			glVertex3f(-1,1,0);
		glEnd();
		glBegin(GL_QUADS);
			glColor3f(0, 0, 255);
			glVertex3f(0, 1, 1);
			glVertex3f(0, -1, 1);
			glVertex3f(0, -1, -1);
			glVertex3f(0, 1, -1);
		glEnd();

		//display list.

		idDp = glGenLists(1);

		glNewList(idDp, GL_COMPILE);
			glBegin(GL_TRIANGLES);
			glVertex3f(0,1,0);
			glVertex3f(1,-1,0);
			glVertex3f(-1,-1,0);
			glEnd();
			
			glTranslatef(0, 2, 0);
			glRotatef(degrees, 0, 1, 0);
			glBegin(GL_TRIANGLES);
			glVertex3f(0,1,0);
			glVertex3f(1,-1,0);
			glVertex3f(-1,-1,0);
			glEnd();
	
			glTranslatef(0, 2, 0);
			glRotatef(degrees, 0, 1, 0);
			glBegin(GL_TRIANGLES);
			glVertex3f(0,1,0);
			glVertex3f(1,-1,0);
			glVertex3f(-1,-1,0);
			glEnd();
			
			glTranslatef(0, 2, 0);
			glRotatef(degrees, 0, 1, 0);
			glBegin(GL_TRIANGLES);
			glVertex3f(0,1,0);
			glVertex3f(1,-1,0);
			glVertex3f(-1,-1,0);
			glEnd();

			glTranslatef(0, 2, 0);
			glRotatef(degrees, 0, 1, 0);
			glBegin(GL_TRIANGLES);
			glVertex3f(0,1,0);
			glVertex3f(1,-1,0);
			glVertex3f(-1,-1,0);
			glEnd();
			
			glTranslatef(0, 2, 0);
			glRotatef(degrees, 0, 1, 0);
			glBegin(GL_TRIANGLES);
			glVertex3f(0, 1, 0);
			glVertex3f(1, -1, 0);
			glVertex3f(-1, -1, 0);
			glEnd();

			glTranslatef(0, 2, 0);
			glRotatef(degrees, 0, 1, 0);
			glBegin(GL_TRIANGLES);
			glVertex3f(0, 1, 0);
			glVertex3f(1, -1, 0);
			glVertex3f(-1, -1, 0);
			glEnd(); 
			
		glEndList();


		for (int i = 0; i < 100; i++) {
			glRotatef(5 * i, 0, 1, 0);
			glPushMatrix();
			glTranslatef(1+ (i*2) % 65, 0, 1 + (i*i) % 70);
			r = (100-i) /100.f;
			g = i / 100.f;
			b = ((i+i)%100) / 100.f;
			glColor3f(r, g, b);
			cout << "( " << r << ", " << g << ", " << b << ")" << endl;
			glCallList(idDp);
			glPopMatrix();
		}

		glDeleteLists(idDp,100);


		//FIN DIBUJAR OBJETOS

		degrees += 360 * hz / fps;
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
					x += sin(camYaw) * 0.1f;
					z -= cos(camYaw) * 0.1f;
					break;
				case SDLK_DOWN:
					x -= sin(camYaw) * 0.1f;
					z += cos(camYaw) * 0.1f;
					break;
				case SDLK_RIGHT:
					camYaw += 0.1f;
					break;
				case SDLK_LEFT:
					camYaw -= 0.1f;
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
