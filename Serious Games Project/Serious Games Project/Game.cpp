#include "Game.h"


void Game::init()
{
	findCorrectCocktail();
	createListOfIngredients();
	findDuplicates();
}

void Game::createListOfIngredients()
{
	findSizeOfArray();
	inputOtherIngredients();

	//take each element from the two arrays and add them to a new array
	for (int i = 0; i <= numberOfGuessingIngredients - 1; i++)
	{
		ingred = correctIngredients[i];
		guessIngredients[i] = ingred;
		ingred = otherIngredients[i];
		guessIngredients[i] = ingred;
	}
}

void Game::findCorrectCocktail()
{
	srand(time(NULL));	//seed RNG
	int option = (rand() % MAX_SIZE);	//find random number 
	randCocktail = cocktails[option];	// use random number to chose a random string from the array

	//opeing file and storing details as variables CORRECT INGREDIENTS
	myfile = ifstream("../Cocktails/Main Menu/" + randCocktail + ".txt");	//finding file from directory
	if (myfile.is_open())
	{
		for (int i = 0; !myfile.eof(); i++)
		{
			myfile >> ingred;
			correctIngredients[i] = ingred;
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

void Game::inputOtherIngredients()
{
	//opeing file and storing details as variables WRONG INGREDIENTS
	myfile = ifstream("../Cocktails/Ingredients.txt");	//finding new file from directory
	if (myfile.is_open())
	{
		for (int i = 0; !myfile.eof(); i++)
		{
			myfile >> ingred;
			otherIngredients[i] += ingred;
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

void Game::findDuplicates()
{
//Finding how many duplicates exist within the array
	for (int i = 0; i <= numberOfGuessingIngredients - 1; i++)
	{
		for (int j = i + 1; j <= numberOfGuessingIngredients; j++)
		{
			if (guessIngredients[i] == guessIngredients[j])
			{
				cout << "DUPLICATION: " << guessIngredients[j] << endl;
				guessIngredients[i] = "DUPLICATE";
			}
		}
	}
}

//get actual size of array
void Game::findSizeOfArray()
{
	string empty = "";
	int i = 0;

	while (correctIngredients[i] != empty)
	{
		i++;
	}

	numberOfCorrectIngredients = i;
	numberOfGuessingIngredients = numberOfCorrectIngredients + numberOfOtherIngredients;
}

void Game::update()
{

}

//get mouse inputs
void Game::mouseInput()
{
	//left mouse button
	if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
	{
		leftPressed = true;
		//cout << "left pressed" << endl;
	}
	else
		leftPressed = false;

	//right mouse button
	if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
	{
		rightPressed = true;
		//cout << "right pressed" << endl;
	}
	else
		rightPressed = false;
}

void Game::draw()
{

}