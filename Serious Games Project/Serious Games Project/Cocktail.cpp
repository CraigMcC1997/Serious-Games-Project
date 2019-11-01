#include "Cocktail.h"

void Cocktail::init()
{
	findCorrectCocktail();
	createListOfIngredients();
	removeDuplicates();
	displayCorrectCocktail();
	displayIngredients();
}

//Find a random cocktail from the array of cocktails and save its ingredients and name
void Cocktail::findCorrectCocktail()
{
	srand(time(NULL));					// seed RNG
	int option = (rand() % MAX_SIZE);	// find random number 
	randCocktail = cocktails[option];	// use random number to chose a random string from the array

	//opeing file and storing details as variables CORRECT INGREDIENTS
	infile = ifstream("../Resources/Cocktails/Main Menu/" + randCocktail + ".txt");	//finding file from directory
	if (infile.is_open())
	{
		for (int i = 0; !infile.eof(); i++)
		{
			infile >> ingredient;
			correctIngredients.push_back(ingredient);
		}
		infile.close();
	}
	else cout << "Unable to open file";
}

//input all the ingredients from the saved file of random ingredients
void Cocktail::inputOtherIngredients()
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

	cout << "SMALLER" << endl;
}



//Create an array of all ingredients by adding the correct and other ingredient arrays together
void Cocktail::createListOfIngredients()
{
	inputOtherIngredients();

	guessIngredients.insert(guessIngredients.end(), correctIngredients.begin(), correctIngredients.end());
	guessIngredients.insert(guessIngredients.end(), otherIngredients.begin(), otherIngredients.end());

	random_shuffle(guessIngredients.begin(), guessIngredients.end());
}


//from the array of all ingredients find the duplicates and "remove" them
void Cocktail::removeDuplicates()
{
	vector<string>::iterator temp;
	sort(guessIngredients.begin(), guessIngredients.end());	//sorting the array in order
	temp = unique(guessIngredients.begin(), guessIngredients.end());	//removing duplicates
	guessIngredients.resize(std::distance(guessIngredients.begin(), temp));	//resizing to remove duplicates memory
}

void Cocktail::displayCorrectCocktail()
{
	int count = 1;
	cout << "\n" << "Correct Cocktail Name: " << "\n" << randCocktail << "\n" << endl;
	cout << "Ingredients: " << endl;

	for (vector<string>::const_iterator i = correctIngredients.begin(); i != correctIngredients.end(); i++)
	{
		cout << count << ". " << *i << endl;
		count++;
	}
}

void Cocktail::displayIngredients()
{
	int count = 1;

	cout << "\n\n\n" << endl;
	cout << "List of Ingredients: " << endl;

	for (vector<string>::const_iterator i = guessIngredients.begin(); i != guessIngredients.end(); i++)
	{
		cout << count << ". " << *i << endl;
		count++;
	}
}

void Cocktail::chooseIngredient()
{
	string choice;
	std::vector<string>::iterator temp;

	cin >> choice;

	if (std::find(correctIngredients.begin(), correctIngredients.end(), choice) != correctIngredients.end()) {
		cout << "found it!" << endl;

		// std :: remove function call 
		temp = correctIngredients.erase(std::remove(correctIngredients.begin(), correctIngredients.end(), choice));
		temp = guessIngredients.erase(std::remove(guessIngredients.begin(), guessIngredients.end(), choice));
		//resize

	}
	else {
		cout << "try again..." << endl;
	}
}

bool Cocktail::allIngredientsFound()
{
	if (correctIngredients.empty())
	{
		foundAll = true;
		cout << "Finished" << endl;
	}
		
	else
	{
		foundAll = false;
		cout << "Keep going" << endl;
	}
		

	return foundAll;
}

void Cocktail::update(SDL_Event sdlEvent)
{
	chooseIngredient();
	//allIngredientsFound();
}

void Cocktail::draw(SDL_Window* window)
{

}