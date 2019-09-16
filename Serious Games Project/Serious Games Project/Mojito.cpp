#include "Mojito.h"

string Mojito::getName()
{
	return name;
}

void Mojito::getIngredients()
{
		/*for (auto const& i : ingredients)
			std::cout << i << "\n";*/

	int size = sizeof(ingredients) / sizeof(ingredients[0]);

	for (int i = 0; i <= size; i++)
		cout << ingredients[i] << endl;
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
