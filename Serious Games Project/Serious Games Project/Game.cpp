#include "Game.h"


void Game::init()
{
	mvpShaderProgram = rt3d::initShaders("../Resources/Shaders/phong-tex.vert", "../Resources/Shaders/phong-tex.frag");

	//Label initialiser
	if (TTF_Init() == -1)
		cout << "TTF failed to initialise." << endl;

	//only font used
	textFont = TTF_OpenFont("../Resources/Fonts/ABOVE.ttf", 28);
	if (textFont == NULL)
		cout << "Failed to open font." << endl;

	labels[0] = 0;


	samples = new HSAMPLE[5];	//array of sound  files
	samples[0] = Sound::loadSample("../Resources/SoundFiles/Jump.wav", BASS_SAMPLE_OVER_POS);	//adding sound files to the array to be played later in code


	vector<GLfloat> verts;
	vector<GLfloat> norms;
	vector<GLfloat> tex_coords;
	vector<GLuint> indices;
	rt3d::loadObj("../Resources/Textures/cube.obj", verts, norms, tex_coords, indices);
	meshIndexCount = indices.size();
	textures[0] = loadTexture::loadTextures("../Resources/Textures/Logo.bmp");
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), indices.size(), indices.data());
	//IMG_Init(IMG_INIT_PNG);
	//textures[0] = loadTexture::loadTextures("../Resources/Textures/Logo.png");

	findCorrectCocktail();
	createListOfIngredients();
	removeDuplicates();
	displayCorrectCocktail();
	displayIngredients();

	cout << "Chose which ingredients are in the cocktail displayed" << endl;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	guessIngredients.resize(std::distance(guessIngredients.begin(), temp));	//resizing to remove duplicates memory
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

void Game::update(SDL_Event sdlEvent)
{
	//!!!!! BREAKS WINDOW !!!!!1
	//if (!foundAll)
	//{
	//	chooseIngredient();
	//}
	//cout << allIngredientsFound() << endl;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	MVP = glm::mat4(1.0f);
	glm::mat4 projection(1.0f);
	glm::mat4 modelview(1.0), MVP(1.0);
	mvStack.push(modelview);
	projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 1.0f, 50.0f);
	rt3d::setUniformMatrix4fv(mvpShaderProgram, "projection", glm::value_ptr(projection));




	glUseProgram(mvpShaderProgram);//Use texture-only shader for text rendering
	glDisable(GL_DEPTH_TEST);//Disable depth test for HUD label

	SDL_Color colour = {255, 255, 255};
	labels[0] = loadTexture::textToTexture(" HUD label ", labels[0], colour, textFont);
	glBindTexture(GL_TEXTURE_2D, labels[0]);
	mvStack.push(glm::mat4(1.0));
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-0.8f, 0.8f, 0.0f));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(0.20f, 0.2f, 0.0f));
	rt3d::setUniformMatrix4fv(mvpShaderProgram, "projection", glm::value_ptr(glm::mat4(1.0)));
	rt3d::setUniformMatrix4fv(mvpShaderProgram, "modelview", glm::value_ptr(mvStack.top()));

	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();
	//glEnable(GL_DEPTH_TEST);//Re-enable depth test after HUD label 
	

	SDL_GL_SwapWindow(window); // swap buffers
}