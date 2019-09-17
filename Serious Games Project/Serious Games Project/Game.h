#pragma once
#include "Mojito.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

	ifstream myfile = ifstream("../Cocktails/Cocktails.txt");

public:
	void init();
	void update();
	void draw();
};

