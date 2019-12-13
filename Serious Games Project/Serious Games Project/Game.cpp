#include "Game.h"

void Game::init()
{
	window = new WindowMaker("Serious Games Coursework", 800, 600,
		glutGet(GLUT_SCREEN_WIDTH) / 2 - windowWidth / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - windowHeight / 2); //placing the window in the middle of the monitor

	//array of sound  files
	samples[0] = Sound::loadSample("../Resources/SoundFiles/correct.wav", BASS_SAMPLE_OVER_POS);	//adding sound files to the array to be played later in code
	samples[1] = Sound::loadSample("../Resources/SoundFiles/wrong.wav", BASS_SAMPLE_OVER_POS);	
	samples[2] = Sound::loadSample("../Resources/SoundFiles/clapping.wav", BASS_SAMPLE_OVER_POS);
	samples[3] = Sound::loadSample("../Resources/SoundFiles/loss.wav", BASS_SAMPLE_OVER_POS);

	setUp();

	cout << "\n\n\n" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "Chose which ingredients are in the cocktail displayed on the game window" << endl;
	cout << "To chose, click on the game window and input any number between 1-99" << endl;
	cout << "Once you have made your decision, press 'c' to connfirm choice " << endl;
	cout << "Repeate this until you have correctly guessed all cocktails" << endl;
	cout << "Or until you lose all three lives" << endl;
	cout << "Good Luck!" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}

void Game::setUp()
{
	correctChoices.clear();
	ingredients->getCocktail()->getCorrectCocktail();
	ingredients->createListOfIngredients();
	ingredients->removeDuplicates();
	//ingredients->getCocktail()->displayCorrectCocktail();
	displayIngredients();
}

//Takes a font, position and text and draws this to screen
void Game::drawString(void* font, float x, float y, string s)
{
	glRasterPos3f(x, y, 0.0);
	for (char i = 0; i < s.length(); ++i)
		glutBitmapCharacter(font, s[i]);
}

bool Game::allIngredientsFound()
{
	if (ingredients->getCocktail()->getIngredients().empty())
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

void Game::displayIngredients()
{
	int count = 1;
	float textX = -1.3f;
	float textY = 0.5f;
	string display;

	drawString(GLUT_BITMAP_TIMES_ROMAN_24, textX, textY, "Possible Ingredients: ");

	for (int i = 0; i < ingredients->getGuessingIngredients().size(); i++)
	{
		if (textY >= -0.2f)
		{
			display += to_string(count) += ". " + ingredients->getGuessingIngredients()[i];		//what text will be displayed
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

void Game::update(float dt)
{
	if (lives <= 0)
	{
		lives = 0;
		alive = false;
		win = false;
	}
	
	if (score->getCorrectCocktails() >= ingredients->getCocktail()->getCocktailsSize())
	{
		alive = false;
		win = true;
	}

	if (ingredients->getCocktail()->getIngredients().empty())
	{
		score->updateCocktailsScore(1);
		setUp();
	}
}

void Game::createNumber(int numOne, int numTwo)
{
	int numChoice = 0;
	stringstream temp;

	if (numOne != NULL)
		temp << to_string(numOne);
	
	if (numTwo != NULL)
	{
		temp << to_string(numTwo);
	}

	temp >> numChoice;

	first = NULL;
	second = NULL;

	if(numChoice <= ingredients->getGuessingIngredients().size())
		checkIngredient(numChoice - 1);
}

void Game::checkIngredient(int choice)
{
	string ingredient = ingredients->getGuessingIngredients()[choice];
	vector<string> correctIngredients = ingredients->getCocktail()->getIngredients();
	
	if (!ingredients->getCocktail()->getIngredients().empty())
	{
		if (find(correctIngredients.begin(), correctIngredients.end(), ingredient) != correctIngredients.end())
		{
			correctChoices.push_back(ingredients->getGuessingIngredients()[choice]);
			ingredients->removeIngredient(ingredient);
			score->updateIngredientScore(1);	//increment ingredient score by 1
			Sound::playSample(samples[0]);
		}
		else
		{
			lives--;
			Sound::playSample(samples[1]);
		}
	}
}

int Game::combine(int x, int y)
{
    int z;
    if(y >= 10)
        x *= 10;
    x *= 10;
    z = x + y;
    return z;
}

void Game::keyboard(unsigned char key, int x, int y)
{
	if (key != 'c')
	{
		switch (key)
		{
		case '0':
		{
			if (first == NULL)
				first = 0;
			else
				second = 0;
				first = combine(first, second);
		}
		break;
		case '1':
		{
			if (first == NULL)
				first = 1;
			else
				second = 1;
		}
		break;
		case '2':
		{
			if (first == NULL)
				first = 2;
			else
				second = 2;
		}
		break;
		case '3':
		{
			if (first == NULL)
				first = 3;
			else
				second = 3;
		}
		break;
		case '4':
		{
			if (first == NULL)
				first = 4;
			else
				second = 4;
		}
		break;
		case '5':
		{
			if (first == NULL)
				first = 5;
			else
				second = 5;
		}
		break;
		case '6':
		{
			if (first == NULL)
				first = 6;
			else
				second = 6;
		}
		break;
		case '7':
		{
			if (first == NULL)
				first = 7;
			else
				second = 7;
		}
		break;
		case '8':
		{
			if (first == NULL)
				first = 8;
			else
				second = 8;
		}
		break;
		case '9':
		{
			if (first == NULL)
				first = 9;
			else
				second = 9;
		}
		break;
		case 's':
			score->saveHighScore();
			break;
		default:
			cout << "incorrect key" << endl;
			break;
		}
	}
	else
		createNumber(first, second);
}

//allows window to be motified during runtime
void Game::ReshapeWindow(int width, int height)
{
	window->Reshape(width, height);
}

void Game::drawAlive()
{
	ingredients->getCocktail()->draw();
	displayIngredients();
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, 0.8, 0.9, "Lives: " + to_string(lives));	//draw text
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, 0.8, 0.8, "Ingredients: " + to_string(score->getCorrectIngredients()));	//draw text
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, 0.8, 0.7, "Complete: " + to_string(score->getCorrectCocktails()));	//draw text
}

void Game::drawDead()
{
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, -1.3, 0.9, "Lives: " + to_string(lives));	//draw text
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, -1.3, 0.8f, "ingredients: " + to_string(score->getCorrectIngredients()));	//draw text
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, -1.3, 0.7f, "Press 's' to save score");	//draw text
	
	if (!playLoss)
	{
		playLoss = true;
		Sound::playSample(samples[3]);
	}
}

void Game::drawWin()
{
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, -1.3, 0.9, "Well done! you got " 
		+ to_string(score->getCorrectCocktails()) + " cocktails correct in a row! "
		+ "YOU WIN!");	//draw text
	
	if (!playClapping)
	{
		playClapping = true;
		Sound::playSample(samples[2]);
	}
}

void Game::draw()
{
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);		// To operate on the model-view matrix
		
	if (alive)	//game running
	{
		drawAlive();
	}
	else 
	{
		if (!win)	
			drawDead();	//lost
		else
			drawWin();	//won
	}

	glutSwapBuffers();				// Swap front and back buffers (of double buffered mode)
}