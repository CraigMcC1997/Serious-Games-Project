#include "Game.h"


void Game::init()
{
	findCorrectCocktail();
	createListOfIngredients();
	MixIngredients();
	removeDuplicates();
	displayCorrectCocktail();

	cout << "Chose which ingredients are in the cocktail displayed" << endl;
}


//Find a random cocktail from the array of cocktails and save its ingredients and name
void Game::findCorrectCocktail()
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
			correctIngredients[i] = ingredient;
		}
		infile.close();
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
	infile = ifstream("../Resources/Cocktails/Ingredients.txt");	//finding new file from directory
	if (infile.is_open())
	{
		for (int i = 0; !infile.eof(); i++)
		{
			infile >> ingredient;
			otherIngredients[i] += ingredient;
		}
		infile.close();
	}
	else cout << "Unable to open file";
}




//from the array of all ingredients find the duplicates and "remove" them
void Game::removeDuplicates()
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
	cout << "\n" << "Correct Cocktail Name: " << "\n" << randCocktail << "\n" << endl;
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
		if (guessIngredients[i] != "DUPLICATE")
			cout << guessIngredients[i] << endl;
}

void Game::saveHighScore()
{
	readHighscore();	//read in & save the current HighScore

	if (currentScore > highScore)	//check that the current score isnt bigger than the saved score
		highScore = currentScore;	//if so, update the highscore

	outFile.open("../Resources/Highscore.txt");
	
	if(outFile.is_open())
		outFile << highScore;
	else cout << "Unable to open file";

	outFile.close();
}

void Game::readHighscore()
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

void Game::MixIngredients()
{
	random_shuffle(begin(guessIngredients), end(guessIngredients) + numberOfCorrectIngredients);	//randomly shuffle the elements in the array	
}

void Game::chooseIngredient()
{
	string choice;

	cin >> choice;

	for (int i = 0; i <= numberOfCorrectIngredients - 1; i++)
	{
		if (correctIngredients[i] == choice)
		{
			cout << "found" << endl;
			correctIngredients[i] = "REMOVED";
		}
		else
			cout << "not found" << endl;
	}
}

bool Game::allIngredientsFound()
{
	bool foundAll = false;

	for (int i = 0; i <= numberOfCorrectIngredients - 1; i++)
	{
		if (correctIngredients[i] != "REMOVED")
			foundAll = false;
		else
			foundAll = true;
	}

	return foundAll;
}



void Game::update()
{
	displayCorrectCocktail();
	displayIngredients();
	chooseIngredient();
	cout << allIngredientsFound() << endl;
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