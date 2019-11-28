#include "Game.h"

void Game::init()
{
	int windowWidth = glutGet(GLUT_SCREEN_WIDTH) - 100;
	int windowHeight = glutGet(GLUT_SCREEN_HEIGHT) - 100;

	window = new WindowMaker("Serious Games Coursework", 800, 600,
		glutGet(GLUT_SCREEN_WIDTH) / 2 - windowWidth / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - windowHeight / 2); //placing the window in the middle of the monitor

	//samples = ;	//array of sound  files
	samples[0] = Sound::loadSample("../Resources/SoundFiles/Click.wav", BASS_SAMPLE_OVER_POS);	//adding sound files to the array to be played later in code
	samples[1] = Sound::loadSample("../Resources/SoundFiles/Click2.wav", BASS_SAMPLE_OVER_POS);	//adding sound files to the array to be played later in code

	cocktail->init();

	cout << "Chose which ingredients are in the cocktail displayed" << endl;
}

//Takes a font, position and text and draws this to screen
void Game::drawString(void* font, float x, float y, string s)
{
	glRasterPos3f(x, y, 0.0);
	for (char i = 0; i < s.length(); ++i)
		glutBitmapCharacter(font, s[i]);
}

void Game::saveHighScore()
{
	readHighscore();	//read in & save the current HighScore

	if (currentScore > highScore)	//check that the current score isnt bigger than the saved score
	{
		highScore = currentScore;	//if so, update the highscore
		
		outFile.open("../Resources/Highscore.txt");
		if (outFile.is_open())
			outFile << highScore;
		else cout << "Unable to open file";
		outFile.close();
	}
	cout << "saved" << endl;
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

void Game::update(float dt)
{
	POINT mousePos;
	GetCursorPos(&mousePos);//tracking the mouse position

	cocktail->update();

	//checking if mouse is inside window
	if (mousePos.x > (window->getXPos()) && mousePos.x < (window->getXPos() + window->getWidth()) &&
		mousePos.y >(window->getYPos()) && mousePos.y < (window->getYPos() + window->getHeight()))
	{
		//get mouse inputs
		mouseInput();
	}
	
	if (lives <= 0)
	{
		lives = 0;
		alive = false;
	}
	
	if (cocktail->getCocktailsComplete() >= 3)
	{
		alive = false;
		win = true;
	}

	
}

//get mouse inputs
void Game::mouseInput()
{
	//left mouse button
	if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
	{
		if (!leftPressed)
		{
			leftPressed = true;
			cout << "left pressed" << endl;
			Sound::playSample(samples[0]);
			//cocktail->checkIngredient("Lime");
		}
	}
	else
		leftPressed = false;

	//right mouse button
	if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
	{
		if (!rightPressed)
		{
			rightPressed = true;
			cout << "right pressed" << endl;
			Sound::playSample(samples[1]);
			//cocktail->checkIngredient("Lime");
		}
	}
	else
		rightPressed = false;
}

void Game::createNumber(int numOne, int numTwo)
{
	string temp;

	if (numOne != NULL)
	{
		temp = to_string(numOne);
		cout << temp << endl;

		if (numTwo != NULL)
		{
			temp += to_string(numTwo);
			cout << temp << endl;
		}
		
		stringstream stringToInt(temp);
		stringToInt >> numChoice;

		first = NULL;
		second = NULL;

		checkIngredient();
	}
	else
		cout << "both values NULL" << endl;
}

void Game::checkIngredient()
{
	if (cocktail->checkIngredient(numChoice - 1))
	{
		currentScore++;
	}
	else
		lives--;
}

void Game::keyboard(unsigned char key, int x, int y)
{
	if (key != 'a')
	{
		switch (key)
		{
		case '0':
		{
			if (first == NULL)
				first = 0;
			else
				second = 0;
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
			saveHighScore();
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
	cocktail->draw();
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, 0.9, 0.9, "Lives: " + to_string(lives));	//draw text
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, 0.9, 0.8, "Score: " + to_string(currentScore));	//draw text
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, 0.9, 0.7, "Complete: " + to_string(cocktail->getCocktailsComplete()));	//draw text
}

void Game::drawDead()
{
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, -1.3, 0.9, "Lives: " + to_string(lives));	//draw text
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, -1.3, 0.8f, "Score: " + to_string(currentScore));	//draw text
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, -1.3, 0.7f, "Press 's' to save score");	//draw text
}

void Game::drawWin()
{
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, -1.3, 0.9, "Well done! you got " 
		+ to_string(cocktail->getCocktailsComplete()) + " cocktails correct in a row!" 
		+ "YOU WIN!");	//draw text
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