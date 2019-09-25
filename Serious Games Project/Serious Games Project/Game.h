#pragma once
#include "Mojito.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h> 

using namespace std;

class Game
{
private:
	Mojito* mojito = new Mojito();

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

	string const cocktails[3] =
	{	"Zombie",
		"Pina Colada",
		"Classic Mojito"
	};

	string randCocktail;

	ifstream myfile; 

public:
	void init();
	void update();
	void draw();
};

