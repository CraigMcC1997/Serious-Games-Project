#pragma once
#include <GL/glew.h>
#include <glut.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <SDL_ttf.h>
#include <algorithm>
#include <time.h> 
#include <algorithm>
#include <fstream>

using namespace std;

class Cocktail
{
private:
	string name;	//selected cocktail
	string ingredient;
	vector<string> correctIngredients;

	ifstream infile;	//file which holds cocktail ingredients
	ofstream outFile;

	vector<string> cocktails =
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

public:
	void init();
	void draw();

	void getCorrectCocktail();
	void displayCorrectCocktail();
	void updateCocktailContainer(vector<string>);
	void RemovePossibleCocktail(string);

	string getName();
	vector<string> getIngredients();
	void drawString(void* font, float x, float y, string s);
};

