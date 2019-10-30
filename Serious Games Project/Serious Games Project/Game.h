#pragma once
#include <GL/glew.h>
#include "PlaySound.h"
#include "loadTexture.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h> 
#include <Windows.h>
#include <mmsystem.h>
#include <algorithm>
#include <vector>
#include <SDL_ttf.h>
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>

using namespace std;
using namespace glm;

class Game
{
private:

	GLuint mvpShaderProgram;
	mat4 MVP;
	std::stack<glm::mat4> mvStack;
	GLuint meshObjects[2];
	GLuint meshIndexCount = 0;



	static int const MAX_SIZE = 9;	//max size of the array of cocktails
	bool mouseActive = false, leftPressed = false, rightPressed = false;	//used for mouse inputs
	int numberOfCorrectIngredients;
	int numberOfOtherIngredients = sizeof(otherIngredients) / sizeof(otherIngredients[0]);	//actual size of array
	int numberOfGuessingIngredients = numberOfCorrectIngredients + numberOfOtherIngredients;

	int highScore, currentScore;
	bool foundAll = false;
	
	string randCocktail;	//selected cocktail
	ifstream infile;	//file which holds cocktail ingredients
	ofstream outFile;
	string ingredient;

	//used for labels
	TTF_Font* textFont;

	//array of Labels
	GLuint labels[5];
	GLuint textures[2];

	//Used by BASS library
	HSAMPLE* samples = NULL;

	bool allowPlay = true;

	string const cocktails[MAX_SIZE] =
	{	
		"Zombie",
		"Pina Colada",
		"Classic Mojito",
		"Long Island Iced Tea",
		"Russian Spy",
		"Rumbull",
		"El Matador",
		"Bird Bath",
		"Gin N Juice"
	};

	static const int SIZE_OF_INGREDIENTS_ARRAY = 21;

	vector<string> otherIngredients;
	vector<string> correctIngredients;
	vector<string> guessIngredients;
	

public:
	Game game() 
	{
	
	}

	void init();
	void update(SDL_Event sdlEvent);
	void mouseInput();
	void draw(SDL_Window* window);

	void findCorrectCocktail();
	void inputOtherIngredients();
	void createListOfIngredients();
	void removeDuplicates();
	void displayCorrectCocktail();
	void displayIngredients();
	void saveHighScore();
	void readHighscore();
	void chooseIngredient();
	bool allIngredientsFound();
};

