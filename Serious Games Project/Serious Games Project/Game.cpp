#include "Game.h"


void Game::init()
{
	findCorrectCocktail();
	createListOfIngredients();
	removeDuplicates();
	displayCorrectCocktail();
	displayIngredients();

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
			correctIngredients.push_back(ingredient);
		}
		infile.close();
	}
	else cout << "Unable to open file";
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
void Game::createListOfIngredients()
{
	inputOtherIngredients();

	guessIngredients.insert(guessIngredients.end(), correctIngredients.begin(), correctIngredients.end());
	guessIngredients.insert(guessIngredients.end(), otherIngredients.begin(), otherIngredients.end());

	random_shuffle(guessIngredients.begin(), guessIngredients.end());
}


//from the array of all ingredients find the duplicates and "remove" them
void Game::removeDuplicates()
{
	vector<string>::iterator temp;
	sort(guessIngredients.begin(), guessIngredients.end());	//sorting the array in order
	temp = unique(guessIngredients.begin(), guessIngredients.end());	//removing duplicates
	guessIngredients.resize(distance(guessIngredients.begin(), temp));	//resizing to remove duplicates memory
}

void Game::displayCorrectCocktail()
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

void Game::displayIngredients()
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

void Game::chooseIngredient()
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

bool Game::allIngredientsFound()
{
	if (correctIngredients.empty())
		foundAll = true;
	else
		foundAll = false;

	return foundAll;
}



void Game::update()
{
	if (!foundAll)
	{
		chooseIngredient();
	}
		
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