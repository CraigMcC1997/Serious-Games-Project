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
	int option;
	string randCocktail;	//selected cocktail
	ifstream myfile;	//file which holds cocktail ingredients
	string ingred;

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

	string wrongIngredients[20] = {};
	string correctIngredients[20] = {};

public:
	Game game() 
	{
	
	}

	void init();
	void update();
	void mouseInput();
	void draw();
	void createListOfIngredients();
};

