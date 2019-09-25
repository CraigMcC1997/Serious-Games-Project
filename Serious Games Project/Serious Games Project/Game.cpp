#include "Game.h"


void Game::init()
{
	srand(time(NULL));	//seed RNG
	int option = (rand() % MAX_SIZE);	//find random number 
	randCocktail = cocktails[option];	// use random number to chose a random string from the array
	myfile = ifstream("../Cocktails/Main Menu/"+ randCocktail + ".txt");	//finding file from directory

	int size = sizeof(cocktails) / sizeof(cocktails[0]);	//actual size of array
	cout << option << endl;	//test code
	cout << cocktails[option] << endl;	//test code

	////chosing a random cocktail
	//for (int i = 0; i < size; i++)
	//{
	//	cout << cocktails[i] << endl;

	//	

	//	//cout << randCocktail << endl;
	//}
		

	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			myfile >> name;
			myfile >> var1;
			myfile >> var2;
			myfile >> var3;
			myfile >> var4;
			myfile >> var5;
			myfile >> var6;
			myfile >> var7;
			myfile >> var8;
			myfile >> var9;
			myfile >> var10;

			cout << name << " " << var1 << " " << var2 << " " << var3 << " " << var4
						<< " " << var5 << " " << var6 << " " << var7 << " " << var8 
						 << " " << var9 << " " << var10 << " " << endl;
		}

		myfile.close();

	}
	else cout << "Unable to open file";
}

void Game::update()
{

}

//get mouse inputs
void Game::mouseInput()
{
	//left mouse button
	if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
	{
		leftPressed = true;
		cout << "left pressed" << endl;
	}
	else
		leftPressed = false;

	//right mouse button
	if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
	{
		rightPressed = true;
		cout << "right pressed" << endl;
	}
	else
		rightPressed = false;
}

void Game::draw()
{

}

