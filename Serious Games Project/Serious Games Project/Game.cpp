#include "Game.h"


void Game::init()
{
	////Label initialiser
	//if (TTF_Init() == -1)
	//	cout << "TTF failed to initialise." << endl;

	////only font used
	//textFont = TTF_OpenFont("ARIEL.ttf", 50);
	//if (textFont == NULL)
	//	cout << "Failed to open font." << endl;

	////Initialize default output device
	//if (!BASS_Init(-1, 44100, 0, 0, NULL))
	//	cout << "Can't initialize device";

	////array of sound  files
	//samples = new HSAMPLE[2];

	////starting the array of labels
	//labels[0] = 0;

	//adding sound files to the array to be played later in code
	//samples[0] = loadSample("SoundFiles/jump.wav");
	//samples[1] = loadSample("SoundFiles/walk.wav");

	findCorrectCocktail();
	createListOfIngredients();
	removeDuplicates();
	displayCorrectCocktail();
	displayIngredients();

	cout << "Chose which ingredients are in the cocktail displayed" << endl;
}

//// textToTexture
//GLuint Game::textToTexture(const char* str, GLuint textID) {
//	GLuint texture = textID;
//	TTF_Font* font = textFont;
//
//	SDL_Surface* stringImage = TTF_RenderText_Blended(font, str, { 255, 255, 255 });
//
//	if (stringImage == NULL) {
//		std::cout << "String surface not created." << std::endl;
//	}
//
//	if (texture == 0) {
//		glGenTextures(1, &texture);//This avoids memory leakage, only initialise //first time 
//	}
//
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, stringImage->w, stringImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, stringImage->pixels);
//	glBindTexture(GL_TEXTURE_2D, NULL);
//
//	SDL_FreeSurface(stringImage);
//	return texture;
//}
//
////clearing the labels text to texture
//void Game::clearTextTexture(GLuint textID) {
//	if (textID != NULL) {
//		glDeleteTextures(1, &textID);
//	}
//}
//
////Loads textures
//GLuint Game::loadBitmap(char* fname)
//{
//	GLuint texID;
//	glGenTextures(1, &texID); // generate texture ID
//
//	// load file - using core SDL library
//	SDL_Surface* tmpSurface;
//	tmpSurface = SDL_LoadBMP(fname);
//	if (!tmpSurface)
//	{
//		std::cout << "Error loading bitmap" << std::endl;
//	}
//
//	// bind texture and set parameters
//	glBindTexture(GL_TEXTURE_2D, texID);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	SDL_PixelFormat* format = tmpSurface->format;
//	GLuint externalFormat, internalFormat;
//
//	if (format->Amask) {
//		internalFormat = GL_RGBA;
//		externalFormat = (format->Rmask < format->Bmask) ? GL_RGBA : GL_BGRA;
//	}
//	else {
//		internalFormat = GL_RGB;
//		externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;
//	}
//
//	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tmpSurface->w, tmpSurface->h, 0,
//		externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SDL_FreeSurface(tmpSurface); // texture loaded, free the temporary buffer
//	return texID;	// return value of texture ID
//}
//
////Loads the sound files
//HSAMPLE Game::loadSample(char* filename)
//{
//	HSAMPLE sam;
//	if (sam = BASS_SampleLoad(FALSE, filename, 0, 0, 3, BASS_SAMPLE_OVER_POS))
//		cout << "sample " << filename << " loaded!" << endl;
//	else
//	{
//		cout << "Can't load sample";
//		exit(0);
//	}
//	return sam;
//}
//
////playing the jumping sound effect
//void Game::playSound(int sound)
//{
//	if (allowPlay) {
//		allowPlay = false;
//		HCHANNEL ch = BASS_SampleGetChannel(samples[sound], FALSE);
//		BASS_ChannelSetAttribute(ch, BASS_ATTRIB_FREQ, 0);
//		BASS_ChannelSetAttribute(ch, BASS_ATTRIB_VOL, 0.5);
//		BASS_ChannelSetAttribute(ch, BASS_ATTRIB_PAN, -1);
//		if (!BASS_ChannelPlay(ch, FALSE))
//			cout << "Can't play sample" << endl;
//	}
//}

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




void Game::draw(SDL_Window* window)
{
	// clearing the screen
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	//labels[0] = textToTexture("object found!", labels[0]);
	//glBindTexture(GL_TEXTURE_2D, labels[0]);

	SDL_GL_SwapWindow(window); // swap buffers
}