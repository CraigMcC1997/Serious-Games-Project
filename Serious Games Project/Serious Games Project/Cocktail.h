#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL_ttf.h>
#include <algorithm>
#include <time.h> 
#include <algorithm>

using namespace std;

class Cocktail
{
private:
	string randCocktail;	//selected cocktail
	ifstream infile;	//file which holds cocktail ingredients
	ofstream outFile;
	string ingredient;

	bool foundAll = false;

	static int const MAX_SIZE = 9;	//max size of the array of cocktails
	int numberOfCorrectIngredients;
	int numberOfOtherIngredients = sizeof(otherIngredients) / sizeof(otherIngredients[0]);	//actual size of array
	int numberOfGuessingIngredients = numberOfCorrectIngredients + numberOfOtherIngredients;

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

	vector<string> otherIngredients;
	vector<string> correctIngredients;
	vector<string> guessIngredients;

public:
	void init();
	void update(SDL_Event sdlEvent);
	void draw(SDL_Window* window);

	void findCorrectCocktail();
	void inputOtherIngredients();
	void createListOfIngredients();
	void removeDuplicates();
	void displayCorrectCocktail();
	void displayIngredients();
	void chooseIngredient();
	bool allIngredientsFound();
};

