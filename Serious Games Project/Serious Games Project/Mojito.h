#pragma once
//#include "AbstractCocktail.h"
#include <list>
#include <string.h>

#include <iostream>

using namespace std;

class Mojito //: AbstractCocktail
{
private:
		static const int MAX_INGREDIENTS = 6;

		static const int MAX_MEASUREMENTS = MAX_INGREDIENTS;

		string name = "Mojito";


		string const ingredients[MAX_INGREDIENTS] =
		{	"50ml Bacardi Blanca",
			"12.5ml lime juice",
			"12.5ml Gomme",
			"Handful of mint leaves", 
			"Crushed Ice", 
			"Soda"
		};

		int measurements[MAX_MEASUREMENTS];
		string method;

public:
	Mojito mojito() {}

	string getName();

	void getIngredients();
	void addIngredient(string);

	int getMeasurement();
	void addMeasurement(int);

	string getMethod();
	void setMethod(string);

};

