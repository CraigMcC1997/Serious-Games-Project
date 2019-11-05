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
	name = cocktails[option];	// use random number to chose a random string from the array

	//opeing file and storing details as variables CORRECT INGREDIENTS
	infile = ifstream("../Resources/Cocktails/Main Menu/" + name + ".txt");	//finding file from directory
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
	cout << "\n" << "Correct Cocktail Name: " << "\n" << name << "\n" << endl;
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
	int x = 0;
	int y = glutGet(GLUT_WINDOW_HEIGHT) - 100;


	drawString(GLUT_BITMAP_HELVETICA_18, x, y, "Possible Ingredients: ");


	for (int i = 0; i < guessIngredients.size(); i++)
	{
		if (y > glutGet(GLUT_WINDOW_HEIGHT) /2)
		{
			y -= 30;
			drawString(GLUT_BITMAP_HELVETICA_18, x, y, count + ". " + guessIngredients[i]);
		}
		else
		{
			y = glutGet(GLUT_WINDOW_HEIGHT) - 100;
			x += 300;
		}
	}
}

//Takes a font, position and text and draws this to screen
void Cocktail::drawString(void* font, float x, float y, string s)
{
	glRasterPos3f(x, y, 0.0);
	for (char i = 0; i < s.length(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
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

string Cocktail::getName()
{
	return name;
}

vector<string> Cocktail::getIngredients()
{
	return guessIngredients;
}

void Cocktail::update()
{
	//chooseIngredient();
	//allIngredientsFound();
}

void Cocktail::draw()
{
	if (name.length() > 0)
		drawString(GLUT_BITMAP_HELVETICA_18, 0, glutGet(GLUT_WINDOW_HEIGHT) - 30, "Name: " + name);

	displayIngredients();
}