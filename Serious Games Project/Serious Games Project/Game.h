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
	
	

	static int const MAX_SIZE = 9;
	bool mouseActive = false, leftPressed = false, rightPressed = false;

	string name;
	string var1;
	string var2;
	string var3;
	string var4;
	string var5;
	string var6;
	string var7;
	string var8;
	string var9;
	string var10;

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

	string randCocktail;

	ifstream myfile; 

public:
	Game game() 
	{
	
	}

	void init();
	void update();
	void mouseInput();
	void draw();
};

