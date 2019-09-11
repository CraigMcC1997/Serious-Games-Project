#include "Mojito.h"

string Mojito::getName()
{
	return name;
}

string Mojito::getIngredients()
{
	string hello = "Mojito";

		for (auto const& i : ingredients)
			std::cout << i << "\n";

	return hello;
}

void Mojito::addIngredient(string ingredient)
{
	//ingredients[10] += ingredient;	//fix this, not correct
}

int Mojito::getMeasurement()
{
	return 0; 
}

void Mojito::addMeasurement(int)
{
}

string Mojito::getMethod()
{
	return string();
}

void Mojito::setMethod(string)
{
}
