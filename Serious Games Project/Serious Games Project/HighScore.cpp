#include "HighScore.h"

void HighScore::saveHighScore()
{
	readHighscore();	//read in & save the current HighScore

	if (correctCocktails > highScore)	//check that the current score isnt bigger than the saved score
	{
		highScore = correctCocktails;	//if so, update the highscore

		outFile.open("../Resources/Highscore.txt");
		if (outFile.is_open())
			outFile << highScore;
		else cout << "Unable to open file";
		outFile.close();
		cout << "saved" << endl;
	}
	else
		cout << "highscore larger than current" << endl;

}

void HighScore::readHighscore()
{
	//opeing file and storing details as variables WRONG INGREDIENTS
	infile = ifstream("../Resources/Highscore.txt");	//finding new file from directory
	if (infile.is_open())
	{
		infile >> highScore;
		cout << highScore << endl;
		infile.close();
	}
	else cout << "Unable to open file";
}

int HighScore::getCorrectIngredients()
{
	return correctIngredients;
}

int HighScore::getCorrectCocktails()
{
	return correctCocktails;
}

void HighScore::updateCocktailsScore(int value)
{
	correctCocktails += value;
}

void HighScore::updateIngredientScore(int value)
{
	correctIngredients += value;
}