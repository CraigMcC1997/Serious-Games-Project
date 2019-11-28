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
		cout << "DEAD" << endl;
	}
	if (cocktail->getCocktailsComplete() >= 1)
	{
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

void Game::keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case '1':
	{
		numChoice = 0;
		if (cocktail->checkIngredient(numChoice))
		{
			currentScore++;
		}
		else
			lives--;
	}
	break;
	case '2':
	{
		numChoice = 1;
		if (cocktail->checkIngredient(numChoice))
		{
			currentScore++;
		}
		else
			lives--;
	}
	break;
	case '3':
	{
		numChoice = 2;
		if (cocktail->checkIngredient(numChoice))
		{
			currentScore++;
		}
		else
			lives--;
	}
	break;
	case '4':
	{
		numChoice = 3;
		if (cocktail->checkIngredient(numChoice))
		{
			currentScore++;
		}
		else
			lives--;
	}
	break;
	case '5':
	{
		numChoice = 4;
		if (cocktail->checkIngredient(numChoice))
		{
			currentScore++;
		}
		else
			lives--;
	}
	break;
	case '6':
	{
		numChoice = 5;
		if (cocktail->checkIngredient(numChoice))
		{
			currentScore++;
		}
		else
			lives--;
	}
	break;
	case '7':
	{
		numChoice = 6;
		if (cocktail->checkIngredient(numChoice))
		{
			currentScore++;
		}
		else
			lives--;
	}
	break;
	case '8':
	{
		numChoice = 7;
		if (cocktail->checkIngredient(numChoice))
		{
			currentScore++;
		}
		else
			lives--;
	}
	break;
	case '9':
	{
		numChoice = 8;
		if (cocktail->checkIngredient(numChoice))
		{
			currentScore++;
		}
		else
			lives--;
	}
	break;
	case 's':
		saveHighScore();
		break;
	default:
		break;
	}
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
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, -1.3, 0.9, "Lives: " + to_string(currentScore));	//draw text
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
		
	if (alive)
	{
		drawAlive();
	}
	else if(!win)
	{
		drawDead();
	}
	else
	{
		drawWin();
	}
		


	glutSwapBuffers();				// Swap front and back buffers (of double buffered mode)
}