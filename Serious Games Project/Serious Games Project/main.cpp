#pragma once
#include <GL/glew.h>
#include <glut.h>
#include <SDL.h>
#include "Timer.h"
#include <iostream>
#include "Game.h"

//#if _DEBUG
//#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
//#endif


Game* game;
LowResTimer timer;
double oldTime = 0;
int refreshMillis = 16;

int width = 600;
int height = 400;
float posx = 140, posy = 90, size = 30;
bool mouseActive = false;
bool clearScreen = true;
float mouseX, mouseY;
float lastX, lastY;

void init()
{
	game = new Game();
	game->init();
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	game->draw();
}

void reshape(GLsizei width, GLsizei height)
{
	game->ReshapeWindow(width, height);
}

void update(int value)
{
	game->update(timer.getTime() - oldTime);
	glutPostRedisplay();
	glutTimerFunc(refreshMillis, update, 0);
	oldTime = timer.getTime();
}

void GLUTRenderer()
{
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, update, 0);
	init();
	glutMainLoop();
}

void cleanUp()
{
	BASS_Free();
	delete game;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	timer.startTimer();
	GLUTRenderer();
	cleanUp();
	return 0;
}

//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//glutInitWindowSize(800, 600);
//glutCreateWindow("Serious Games Coursework");
//glClearColor(0.0, 0.0, 0.0, 0.0);
//gluOrtho2D(0, 800, 0, 600);