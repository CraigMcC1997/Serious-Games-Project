#include "Game.h"

GLfloat colours[] = { 1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f,
					0.0f, 1.0f, 0.0f,
					1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f
};


GLfloat vertices6[] = { 0.0f, 1.0f, 0.0f,
						1.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 0.0f,
						1.0f, 1.0f, 0.0f,
						1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f
};

void Game::init()
{
	shaderProgram = rt3d::initShaders("../Resources/Shaders/minimal.vert", "../Resources/Shaders/minimal.frag");
	meshObjects[0] = rt3d::createColourMesh(4, vertices6, colours);

	samples = new HSAMPLE[5];	//array of sound  files
	samples[0] = Sound::loadSample("../Resources/SoundFiles/Jump.wav", BASS_SAMPLE_OVER_POS);	//adding sound files to the array to be played later in code

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

void Game::update(SDL_Event sdlEvent)
{
	cout << "test" << endl;
	cocktail->update(sdlEvent);
}


//get mouse inputs
void Game::mouseInput()
{
	//left mouse button
	if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
	{
		leftPressed = true;
		Sound::playSample(samples[0]);
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



void Game::draw(SDL_Window* window)
{
	// clear the screen
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	cocktail->draw(window);

	rt3d::drawMesh(meshObjects[0], 6, GL_TRIANGLES);

	SDL_GL_SwapWindow(window); // swap buffers
}