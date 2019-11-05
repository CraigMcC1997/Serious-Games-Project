#pragma once
#include <GL/glew.h>
#include <glut.h>
#include <SDL.h>
#include <iostream>
#include "Window.h"
#include "Game.h"

//#if _DEBUG
//#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
//#endif


Game* game;
POINT mousePos;
Window* hWindow;
SDL_GLContext glContext; // OpenGL context handle


int width = 600;
int height = 400;
float posx = 140, posy = 90, size = 30;
bool mouseActive = false;
bool clearScreen = true;
float mouseX, mouseY;
float lastX, lastY;



bool handleSDLEvent(SDL_Event const& sdlEvent)
{
	if (sdlEvent.type == SDL_QUIT)
		return false;
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		// Can extend this to handle a wider range of keys
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			return false;
		default:
			break;
		}
	}
	return true;
}

void exitFatalError(char* message)
{
	cout << message << " " << endl;
	cout << SDL_GetError();
	SDL_Quit();
	exit(1);
}

void init()
{
	game = new Game();
	game->init();
}

void update()
{
	//game->update();

	GetCursorPos(&mousePos);	//tracking the mouse position
	
	
	//if (mousePos.x > (hWindow->getXPos()) && mousePos.x < (hWindow->getXPos() + hWindow->getWidth()) &&		//checking if the mouse in in the window
	//	mousePos.y >(hWindow->getYPos()) && mousePos.y < (hWindow->getYPos() + hWindow->getHeight()))
	//{
	//	game->mouseInput();	//checking for mouse inputs
	//}
}



void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glVertex2f(lastX, lastY);
	glVertex2f(mouseX, mouseY);
	lastX = mouseX;
	lastY = mouseY;
	glEnd();

	game->draw();
	glutSwapBuffers();
}

void cleanUp()
{
	BASS_Free();
}

void mouse(int button, int state, int x, int y) {
	if (!state) {
		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Serious Games Coursework");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0, 800, 0, 600);
	init();
	update();
	glutDisplayFunc(draw);
	glutMouseFunc(mouse);
	glutMainLoop();
	cleanUp();
	return 0;
}