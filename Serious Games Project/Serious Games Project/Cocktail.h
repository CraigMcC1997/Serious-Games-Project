#pragma once
#include <GL/glew.h>
#include <glut.h>
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
	string name;	//selected cocktail
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
	vector<string> correctChoices;

	void removeIngredient(string choice);

public:
	void init();
	void update();
	void draw();

	void getCorrectCocktail();
	void inputOtherIngredients();
	void createListOfIngredients();
	void removeDuplicates();
	void displayCorrectCocktail();
	void displayIngredients();
	bool allIngredientsFound();

	string getName();
	vector<string> getIngredients();
	void drawString(void* font, float x, float y, string s);
	void createHitbox(string, int, int);
	bool checkIngredient(int choice);
};

