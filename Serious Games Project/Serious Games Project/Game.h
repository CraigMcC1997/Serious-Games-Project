#pragma once
#include <GL/glew.h>
#include "PlaySound.h"
#include "loadTexture.h"
#include <Windows.h>
#include <mmsystem.h>
#include <SDL_ttf.h>
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>

#include "Cocktail.h"

using namespace std;
using namespace glm;

class Game
{
private:
	Cocktail* cocktail = new Cocktail();


	GLuint shaderProgram;
	mat4 MVP;
	std::stack<glm::mat4> mvStack;
	GLuint meshObjects[2];
	GLuint meshIndexCount = 0;

	bool mouseActive = false, leftPressed = false, rightPressed = false;	//used for mouse inputs
	int highScore, currentScore;
	
	ifstream infile;	//file which holds cocktail ingredients
	ofstream outFile;

	//used for labels
	TTF_Font* textFont;

	//array of Labels
	GLuint labels[5];
	GLuint textures[5];

	//Used by BASS library
	HSAMPLE* samples = NULL;

	bool allowPlay = true;

	

public:
	Game game() 
	{
	
	}

	void init();
	void update(SDL_Event sdlEvent);
	void mouseInput();
	void draw(SDL_Window* window);


	void saveHighScore();
	void readHighscore();
};