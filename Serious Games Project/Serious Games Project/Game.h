#pragma once
#include "Mojito.h"
#include <iostream>

using namespace std;

class Game
{
private:
	Mojito* mojito = new Mojito();
public:
	void init();
	void update();
	void draw();
};

