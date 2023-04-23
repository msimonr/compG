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

	float color = 0.3;
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
	float colores[8][3] = { {0,0,0},{1,0,0},{0,1,0},{1,1,0},{0,0,1},{1,0,1},{0,1,1},{1,1,1} };
	bool sube = true;
	//LOOP PRINCIPAL
	do{
		int tick = SDL_GetTicks();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		//TRANSFORMACIONES LINEALES

		//DIBUJAR OBJETOS

		glPushMatrix();

		glTranslatef(0, -2.8, 0);
		for (int i = 0; i < 8; i++) {
			glBegin(GL_QUADS);
				glColor3f(colores[i][0], colores[i][1], colores[i][2]);
				glVertex3f(4, 0.7 * (i), -1);
				glVertex3f(4, 0.7 * (i+1), -1);
				glVertex3f(-4, 0.7 * (i+1), -1);
				glVertex3f(-4, 0.7 * i, -1);
			glEnd();
		}
		glPopMatrix();

		glTranslatef(-2.8, 0, 0);
		for (int i = 0; i < 8; i++) {
			glBegin(GL_QUADS);
				glColor4f(colores[i][0], colores[i][1], colores[i][2], degrees);
				glVertex3f(0.7 * (i), 2.7, 0);
				glVertex3f(0.7 * (i + 1), 2.7, 0);
				glVertex3f(0.7 * (i + 1), -2.7, 0);
				glVertex3f(0.7 * i, -2.7, 0);
			glEnd();
		}

		//FIN DIBUJAR OBJETOS

		if (degrees > 1 || degrees < 0) {
			sube = !sube;
		}

		if(sube){
			degrees += 1 * hz / 60;
			cout << degrees <<endl;
		}
		else {
			degrees -= 1 * hz / 60;
		}

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

string lectura(string path) {
	ifstream file;
	string content;
	string res;

	file.open(path, ios::in);

	if (file.fail()) {
		cerr << "Ocurrio un error al abrir el arcchivo"<<endl;
		exit(1);
	}
	
	while (!file.eof()) {
		getline(file, content);
		res += content+"\n";

	}
	return res;
}

//Crea un vector de floats, a partir de un string. 
// Precondici�nes: 
// 1. Coordenadas separadas por espacios. 
// 2. Las coordenadas deben ser del tipo �n� o �n.n" o ".n" con n numero.
vector<float> string2vectorFloat(string lista) {
	int i = 0;
	vector<float> res;
	while (lista[i] != '\n') {
		if (int(lista[i]) == 46 || int(lista[i]) == 45 || int(lista[i]) > 47 && int(lista[i]) < 58) {
			string aux;
			while (lista[i] != ' ' && lista[i] != '\n') {
				aux += lista[i];
				i++;
			}
			res.push_back(stof(aux));
		}else if(int(lista[i]) < 91 && int(lista[i]) > 64) {
			//Letra como ord.
			res.push_back(int(lista[i])/1.f);
			i++;
		}
		else {
			i++;
		}
	}
	return res;
}

list<vector<float>> cargarVertices(string lista) {
	int first = 0;
	int last = 0;
	string::iterator endline = lista.begin();
	string::iterator end = lista.end();
	list<vector<float>> res;

	while (endline != end) {
		if (*endline != '\n') {
			endline++;
			last++;
		}
		else {
			endline++;
			last++;
			res.push_back(string2vectorFloat(lista.substr(first, last)));
			first = last;
		}
	}

	return res;
}