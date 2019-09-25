#include "Game.h"


void Game::init()
{
	srand(time(NULL));	//seed RNG
	int option = (rand() % 3);	//find random number 
	randCocktail = cocktails[option];	// use random number to chose a random string from the array
	myfile = ifstream("../Cocktails/Main Menu/"+ randCocktail + ".txt");

	int size = sizeof(cocktails) / sizeof(cocktails[0]);
	cout << option << endl;
	cout << cocktails[option] << endl;

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
	string playerwords;

	cin >> playerwords;
}

void Game::draw()
{

}

