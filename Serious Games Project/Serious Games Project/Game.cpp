#include "Game.h"


void Game::init()
{
	srand(time(NULL));	//seed RNG
	option = (rand() % MAX_SIZE);	//find random number 
	randCocktail = cocktails[option];	// use random number to chose a random string from the array
	

	int size = sizeof(cocktails) / sizeof(cocktails[0]);	//actual size of array
	cout << option << endl;	//test code
	cout << randCocktail << endl;	//test code

	//opeing file and storing details as variables CORRECT INGREDIENTS
	myfile = ifstream("../Cocktails/Main Menu/" + randCocktail + ".txt");	//finding file from directory
	if (myfile.is_open())
	{
		for (int i = 0; !myfile.eof(); i++)
		{
			myfile >> ingred;
			correctIngredients[i] += ingred;
			cout << correctIngredients[i] << endl;
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	cout << "\n\n\n\n";
	
	//opeing file and storing details as variables WRONG INGREDIENTS
	myfile = ifstream("../Cocktails/Ingredients.txt");	//finding new file from directory
	if (myfile.is_open())
	{
		for (int i = 0; !myfile.eof(); i++)
		{
			myfile >> ingred;
			wrongIngredients[i] += ingred;
			cout << wrongIngredients[i] << endl;
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

void Game::createListOfIngredients()
{
	//	input file of ingredients and store variables as wrong ingredients array.
	//	grab correct ingredients and store copy.
	//	take both arrays and create a new array as a randomly generated array of ingredients
	//	of the above two arrays (add correct ingredients to the array and then mix in randomly the wrong ingredients)
	//	display new array for testing
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
		cout << "left pressed" << endl;
	}
	else
		leftPressed = false;

	//right mouse button
	if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
	{
		rightPressed = true;
		cout << "right pressed" << endl;
	}
	else
		rightPressed = false;
}

void Game::draw()
{

}