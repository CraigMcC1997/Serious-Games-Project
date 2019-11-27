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
			cocktail->removeIngredient("Lime");
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
			cocktail->removeIngredient("Lime");
		}
	}
	else
		rightPressed = false;
}

void Game::keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		cout << "a" << endl;
		break;
	case 'b':
		cout << "b" << endl;
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

void Game::draw()
{
	// clear the screen
	//glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);		// To operate on the model-view matrix
		
	cocktail->draw();

	glutSwapBuffers();				// Swap front and back buffers (of double buffered mode)
}