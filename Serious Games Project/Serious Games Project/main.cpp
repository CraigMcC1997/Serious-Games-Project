#pragma once
#include <GL/glew.h>
#include <glut.h>
#include <SDL.h>
#include "Timer.h"
#include <iostream>
#include "Game.h"

#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif


Game* game;
LowResTimer timer;
double oldTime = 0;
int refreshMillis = 16;

unsigned char key;
int x;
int y;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}

void draw()
{
	game->draw();
}

void reshape(GLsizei width, GLsizei height)
{
	game->ReshapeWindow(width, height);
}

void keyboard(unsigned char key, int x, int y)
{
	game->keyboard(key, x, y);
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
	glutKeyboardFunc(keyboard);
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
	game = new Game();
	game->init();
	timer.startTimer();
	GLUTRenderer();
	cleanUp();
	return 0;
}