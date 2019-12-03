#include "GuessingIngredients.h"

//input all the ingredients from the saved file of random ingredients
//shuffle the ingredients and shrink to only hold 10
void GuessingIngredients::inputWrongIngredients()
{
	//opeing file and storing details as variables WRONG INGREDIENTS
	infile = ifstream("../Resources/Cocktails/Ingredients.txt");	//finding new file from directory
	if (infile.is_open())
	{
		for (int i = 0; !infile.eof(); i++)
		{
			infile >> ingredient;
			otherIngredients.push_back(ingredient);
		}
		infile.close();
	}
	else cout << "Unable to open file";

	random_shuffle(otherIngredients.begin(), otherIngredients.end());
	otherIngredients.resize(10);
}

//Create an array of all ingredients by adding the correct and other ingredient arrays together
void GuessingIngredients::createListOfIngredients()
{
	inputWrongIngredients();

	vector<string> temp = cocktail->getIngredients();

	guessIngredients.insert(guessIngredients.end(), temp.begin(), temp.end());
	guessIngredients.insert(guessIngredients.end(), otherIngredients.begin(), otherIngredients.end());
}

//from the container of all ingredients find the duplicates and "remove" them
void GuessingIngredients::removeDuplicates()
{
	vector<string>::iterator temp;
	sort(guessIngredients.begin(), guessIngredients.end());	//sorting the container in order
	temp = unique(guessIngredients.begin(), guessIngredients.end());	//removing duplicates
	guessIngredients.resize(distance(guessIngredients.begin(), temp));	//resizing to remove duplicates memory
	random_shuffle(guessIngredients.begin(), guessIngredients.end());	//unsorting order
}

void GuessingIngredients::removeIngredient(string choice)
{
	vector<string>::iterator temp;
	vector<string> cocktailIngredients = cocktail->getIngredients();

	//remove ingredient from containers 
	temp = cocktailIngredients.erase(remove(cocktailIngredients.begin(),
		cocktailIngredients.end(), choice));
	temp = guessIngredients.erase(remove(guessIngredients.begin(), guessIngredients.end(), choice));
	guessIngredients.resize(distance(guessIngredients.begin(), temp));	//resizing to remove duplicates memory
	
	cocktail->updateCocktailContainer(cocktailIngredients);

	cocktail->displayCorrectCocktail();
}

vector<string> GuessingIngredients::getGuessingIngredients()
{
	return guessIngredients;
}

Cocktail* GuessingIngredients::getCocktail()
{
	return cocktail;
}