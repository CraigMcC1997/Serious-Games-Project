#include "Cocktail.h"

void Cocktail::init()
{
	getCorrectCocktail();
	createListOfIngredients();
	removeDuplicates();
	displayCorrectCocktail();
	displayIngredients();
}

//Find a random cocktail from the array of cocktails and save its ingredients and name
void Cocktail::getCorrectCocktail()
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
//shuffle the ingredients and shrink to only hold 10
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
}

//Create an array of all ingredients by adding the correct and other ingredient arrays together
void Cocktail::createListOfIngredients()
{
	inputOtherIngredients();

	guessIngredients.insert(guessIngredients.end(), correctIngredients.begin(), correctIngredients.end());
	guessIngredients.insert(guessIngredients.end(), otherIngredients.begin(), otherIngredients.end());
}


//from the array of all ingredients find the duplicates and "remove" them
void Cocktail::removeDuplicates()
{
	vector<string>::iterator temp;
	sort(guessIngredients.begin(), guessIngredients.end());	//sorting the container in order
	temp = unique(guessIngredients.begin(), guessIngredients.end());	//removing duplicates
	guessIngredients.resize(std::distance(guessIngredients.begin(), temp));	//resizing to remove duplicates memory
	random_shuffle(guessIngredients.begin(), guessIngredients.end());	//unsorting order
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

void Cocktail::displayIngredients()
{
	int count = 1;
	float textX = -1.3f;
	float textY = 0.5f;
	string display;

	drawString(GLUT_BITMAP_TIMES_ROMAN_24, textX, textY, "Possible Ingredients: ");
	
	for (int i = 0; i < guessIngredients.size(); i++)
	{
		if (textY >= -0.2f)
		{
			display += to_string(count) += ". " + guessIngredients[i];		//what text will be displayed
			textY -= 0.1f;													//moving text down
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, textX, textY, display);	//draw text
			//createHitbox(guessIngredients[i], textX, textY);
			count++;														//Increase count
			display = "";													//reset string
		}
		if (textY <= -0.2f)												//if text gets below screen
		{																//move text up and across
			textY = 0.5f;
			textX += 0.8f;
		}
	}
	count = 1;

	textX = -1.3f;
	textY = -0.7f;

	drawString(GLUT_BITMAP_TIMES_ROMAN_24, textX, textY, "Correct Ingredients: ");

	if (correctChoices.size() != 0) {
		for (int i = 0; i < correctChoices.size(); i++)
		{
			display += to_string(count) += ". " + correctChoices[i];		//what text will be displayed
			textY -= 0.1f;													//moving text down
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, textX, textY, display);	//draw text
			//createHitbox(guessIngredients[i], textX, textY);
			count++;														//Increase count
			display = "";													//reset string

			if (textY <= -0.9f)												//if text gets below screen
			{																//move text up and across
				textY = -0.7f;
				textX += 0.8f;
			}
		}
	}
}

//Takes a font, position and text and draws this to screen
void Cocktail::drawString(void* font, float x, float y, string s)
{
	glRasterPos2f(x, y);
	for (char i = 0; i < s.length(); ++i)
		glutBitmapCharacter(font, s[i]);
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

void Cocktail::removeIngredient(string choice)
{
	std::vector<string>::iterator temp;

	//remove ingredient from containers 
	temp = correctIngredients.erase(std::remove(correctIngredients.begin(), correctIngredients.end(), choice));
	temp = guessIngredients.erase(std::remove(guessIngredients.begin(), guessIngredients.end(), choice));
	guessIngredients.resize(std::distance(guessIngredients.begin(), temp));	//resizing to remove duplicates memory
	displayCorrectCocktail();

	correctChoices.push_back(choice);
}

string Cocktail::getName()
{
	return name;
}

vector<string> Cocktail::getIngredients()
{
	return guessIngredients;
}

bool Cocktail::checkIngredient(int choice)
{
	bool found = false;
	string ingredient = guessIngredients[choice];
	cout << guessIngredients[choice] << endl;
	if (!correctIngredients.empty())
	{
		if (std::find(correctIngredients.begin(), correctIngredients.end(), ingredient) != correctIngredients.end())
		{
			removeIngredient(ingredient);
			found = true;
		}
		else
			cout << "not found";
	}
	return found;
}

void Cocktail::setUp()
{
	correctChoices.clear();
	getCorrectCocktail();
	createListOfIngredients();
	removeDuplicates();
	displayCorrectCocktail();
	displayIngredients();
}

int Cocktail::getCocktailsComplete()
{
	return cocktailsComplete;
}

void Cocktail::update()
{
	if (correctIngredients.empty())
	{
		cocktailsComplete++;
		setUp();
	}
}

void Cocktail::draw()
{
	if (name.length() > 0)
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, -1.3, 0.9, "Name: " + name);

	displayIngredients();
}