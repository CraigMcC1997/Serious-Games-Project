#pragma once
#include <GL/glew.h>
#include <glut.h>
#include "PlaySound.h"
#include <Windows.h>
#include <mmsystem.h>
#include "WindowMaker.h"
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "HighScore.h"
#include "GuessingIngredients.h"
#include <sstream>

using namespace std;
using namespace glm;

class Game
{
private:
	int windowWidth = glutGet(GLUT_SCREEN_WIDTH) - 100;
	int windowHeight = glutGet(GLUT_SCREEN_HEIGHT) - 100;
	WindowMaker* window;
	GuessingIngredients* ingredients = new GuessingIngredients();
	HighScore* score = new HighScore();

	bool foundAll = false;

	bool mouseActive = false, leftPressed = false, rightPressed = false;	//used for mouse inputs
	
	int lives = 3;
	bool alive = true, win = false, playClapping = false, playLoss = false;

	//Used by BASS library
	HSAMPLE* samples = new HSAMPLE[5];

	bool allowPlay = true;

	int x = 200, y = 100;

	int first = NULL;
	int second = NULL;

	vector<string> correctChoices;

public:
	Game game() {}

	void init();
	void update(float dt);
	void draw();
	void setUp();
	void ReshapeWindow(int weigth, int height);
	
	
	void drawString(void* font, float x, float y, string s);
	void drawAlive();
	void drawDead();
	void drawWin();
	void displayIngredients();
	
	bool allIngredientsFound();
	void checkIngredient(int choice);

	void createNumber(int first, int second);
	int combine(int x, int y);

	void keyboard(unsigned char key, int x, int y);
};