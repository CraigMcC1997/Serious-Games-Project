/*
Name: Craig McCorrisken
Student ID: B00317267
I declare that the following code was produced by Craig McCorrisken, Sean L. Dornan & Mariusz Stepien as a group assignment for the Game Physics module and that this is our own work.
I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/

#pragma once
#include <glut.h>

class WindowMaker
{
private:
	double clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
	int width, height, xPos, yPos;

public:
	WindowMaker(const char* windowName, int width, int height, int xPos, int yPos): width(width), height(height), xPos(xPos), yPos(yPos)
	{
		glutInitDisplayMode(GLUT_DOUBLE);	// Enable double buffered mode
		glutInitWindowSize(width, height);	// Initial window width and height
		glutInitWindowPosition(xPos, yPos);
		glutCreateWindow(windowName);			// Create window with given title
	}

	virtual ~WindowMaker() {}

	void Reshape(GLsizei width, GLsizei height);
	int getWidth();
	int getHeight();
	int getXPos();
	int getYPos();
};