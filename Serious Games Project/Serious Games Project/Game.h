#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h> 
#include <Windows.h>
#include <algorithm>
#include <vector>

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
	void update();
	void mouseInput();
	void draw();

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

