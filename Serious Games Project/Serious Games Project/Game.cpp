#include "Game.h"


void Game::init()
{
	findCorrectCocktail();
	createListOfIngredients();
	findDuplicates();
	displayCorrectCocktail();
	displayIngredients();
}



//Find a random cocktail from the array of cocktails and save its ingredients and name
void Game::findCorrectCocktail()
{
	srand(time(NULL));					//seed RNG
	int option = (rand() % MAX_SIZE);	//find random number 
	randCocktail = cocktails[option];	// use random number to chose a random string from the array

	//opeing file and storing details as variables CORRECT INGREDIENTS
	myfile = ifstream("../Cocktails/Main Menu/" + randCocktail + ".txt");	//finding file from directory
	if (myfile.is_open())
	{
		for (int i = 0; !myfile.eof(); i++)
		{
			myfile >> ingredient;
			correctIngredients[i] = ingredient;
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}



//Create an array of all ingredients by adding the correct and other ingredient arrays together
void Game::createListOfIngredients()
{
	findSizeOfArray();
	inputOtherIngredients();

	//take each element from the two arrays and add them to a new array
	for (int i = 0; i <= numberOfGuessingIngredients - 1; i++)
	{
		ingredient = correctIngredients[i];
		guessIngredients[i] = ingredient;
		ingredient = otherIngredients[i];
		guessIngredients[i] = ingredient;
	}
}




//get actual size of array of all the ingredients
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




//input all the ingredients from the saved file of random ingredients
void Game::inputOtherIngredients()
{
	//opeing file and storing details as variables WRONG INGREDIENTS
	myfile = ifstream("../Cocktails/Ingredients.txt");	//finding new file from directory
	if (myfile.is_open())
	{
		for (int i = 0; !myfile.eof(); i++)
		{
			myfile >> ingredient;
			otherIngredients[i] += ingredient;
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}




//from the array of all ingredients find the duplicates and "remove" them
void Game::findDuplicates()
{
//Finding how many duplicates exist within the array
	for (int i = 0; i <= numberOfGuessingIngredients - 1; i++)
	{
		for (int j = i + 1; j <= numberOfGuessingIngredients; j++)
		{
			if (guessIngredients[i] == guessIngredients[j])
			{
				guessIngredients[i] = "DUPLICATE";	//!!!!UPDATE, ELEMENT IS NOT ACTUALLY REMOVED, ONLY CHANGED NAME
			}
		}
	}
}

void Game::displayCorrectCocktail()
{
	int count = 1;

	cout << "\n\n\n" << endl;
	cout << "Correct Cocktail Name: " << "\n" << randCocktail << "\n" << endl;
	cout << "Ingredients: " << endl;

	for (int i = 0; i <= numberOfCorrectIngredients - 1; i++)
	{
		cout << count << ". " << correctIngredients[i] << endl;
		count++;
	}	
}

void Game::displayIngredients()
{
	cout << "\n\n\n" << endl;
	cout << "List of Ingredients: " << endl;

	for (int i = 0; i < numberOfGuessingIngredients; i++)
		cout << guessIngredients[i] << endl;
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