/*
Name: Craig McCorrisken
Student ID: B00317267
I declare that the following code was produced by Craig McCorrisken, Sean L. Dornan & Mariusz Stepien as a group assignment for the Game Physics module and that this is our own work.
I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/

#pragma once
#include "WindowMaker.h"

void WindowMaker::Reshape(GLsizei width, GLsizei height)
{
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	if (width >= height) {
		clipAreaXLeft = -1.0 * aspect;
		clipAreaXRight = 1.0 * aspect;
		clipAreaYBottom = -1.0;
		clipAreaYTop = 1.0;
	}
	else {
		clipAreaXLeft = -1.0;
		clipAreaXRight = 1.0;
		clipAreaYBottom = -1.0 / aspect;
		clipAreaYTop = 1.0 / aspect;
	}
	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
}

int WindowMaker::getWidth()
{
	return width;
}

int WindowMaker::getHeight()
{
	return height;
}

int WindowMaker::getXPos()
{
	return glutGet((GLenum)GLUT_WINDOW_X);
}

int WindowMaker::getYPos()
{
	return glutGet((GLenum)GLUT_WINDOW_Y);
}
