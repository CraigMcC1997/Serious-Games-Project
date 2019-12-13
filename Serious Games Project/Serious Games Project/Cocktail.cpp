#include "Cocktail.h"

//Takes a font, position and text and draws this to screen
void Cocktail::drawString(void* font, float x, float y, string s)
{
	glRasterPos2f(x, y);
	for (char i = 0; i < s.length(); ++i)
		glutBitmapCharacter(font, s[i]);
}

//Find a random cocktail from the array of cocktails and save its ingredients and name
void Cocktail::getCorrectCocktail()
{
	srand(time(NULL));					// seed RNG
	int option = (rand() % cocktails.size());	// find random number 
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

	cout << "found a cocktail";

	RemovePossibleCocktail(name);
}

//FOR TESTING PURPOSES ONLY!!!
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

void Cocktail::updateCocktailContainer(vector<string> newContainer)
{
	correctIngredients = newContainer;
}

void Cocktail::RemovePossibleCocktail(string cocktail)
{
	vector<string>::iterator temp;

	//remove ingredient from containers 
	temp = cocktails.erase(remove(cocktails.begin(),
		cocktails.end(), cocktail));
	cocktails.resize(distance(cocktails.begin(), temp));	//resizing to remove duplicates memory

	//int count = 1;
	//for (vector<string>::const_iterator i = cocktails.begin(); i != cocktails.end(); i++)
	//{
	//	cout << count << ". " << *i << endl;
	//	count++;
	//}
}

int Cocktail::getCocktailsSize()
{
	return cocktails.size();
}

string Cocktail::getName()
{
	return name;
}

vector<string> Cocktail::getIngredients()
{
	return correctIngredients;
}

void Cocktail::draw()
{
	if (name.length() > 0)
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, -1.3, 0.9, "Name: " + name);
}