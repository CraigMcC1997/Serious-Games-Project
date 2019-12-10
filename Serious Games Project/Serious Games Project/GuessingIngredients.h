#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Cocktail.h"

using namespace std;

class GuessingIngredients
{
private:
	Cocktail* cocktail = new Cocktail();

	ifstream infile;
	string ingredient;
	vector<string> otherIngredients;
	vector<string> guessIngredients;

public:
	GuessingIngredients()
	{
		//cocktail->init();
	};

	void inputWrongIngredients();
	void createListOfIngredients();
	void removeDuplicates();
	void removeIngredient(string choice);

	vector<string> getGuessingIngredients();

	Cocktail* getCocktail();
};

