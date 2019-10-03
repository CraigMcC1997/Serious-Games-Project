#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h> 
#include <Windows.h>

using namespace std;

class Game
{
private:
	static int const MAX_SIZE = 9;	//max size of the array of cocktails
	bool mouseActive = false, leftPressed = false, rightPressed = false;	//used for mouse inputs
	int numberOfCorrectIngredients = sizeof(correctIngredients) / sizeof(correctIngredients[0]);	//actual size of array
	int numberOfOtherIngredients = sizeof(otherIngredients) / sizeof(otherIngredients[0]);	//actual size of array
	int numberOfGuessingIngredients = numberOfCorrectIngredients + numberOfOtherIngredients;
	
	string randCocktail;	//selected cocktail
	ifstream myfile;	//file which holds cocktail ingredients
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

	string otherIngredients[SIZE_OF_INGREDIENTS_ARRAY] = {};
	string correctIngredients[10] = {};
	string guessIngredients[SIZE_OF_INGREDIENTS_ARRAY] = {};
	

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
	void findSizeOfArray();
	void findDuplicates();
};

