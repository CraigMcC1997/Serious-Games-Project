#pragma once
#include "Mojito.h"
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
	string var5;
	string var6;
	string var7;
	string var8;
	string var9;
	string var10;

	ifstream myfile = ifstream("../Cocktails/Cocktails.txt");

public:
	void init();
	void update();
	void draw();
};

