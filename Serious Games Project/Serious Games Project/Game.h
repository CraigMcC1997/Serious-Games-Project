#pragma once
#include <GL/glew.h>
#include "PlaySound.h"
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

using namespace std;

class Game
{
private:
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

	////used for labels
	//TTF_Font* textFont;

	////array of Labels
	//GLuint labels[5];

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
	//GLuint textToTexture(const char* str, GLuint textID);
	//void clearTextTexture(GLuint textID);
	//GLuint loadBitmap(char* fname);
};

