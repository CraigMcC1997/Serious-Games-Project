#pragma once
#include <fstream>
#include <iostream>

using namespace std;

class HighScore
{
private:
	int highScore;
	int correctIngredients = 0;
	int correctCocktails = 0;

	ifstream infile;	//file which holds cocktail ingredients
	ofstream outFile;

public:
	void saveHighScore();
	void readHighscore();

	int getCorrectIngredients();
	int getCorrectCocktails();
	void updateIngredientScore(int);
	void updateCocktailsScore(int);
};