#include "Game.h"


void Game::init()
{
	cout << mojito->getName() << endl;
	mojito->getIngredients();

	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			myfile >> name;
			myfile >> var1;
			myfile >> var2;
			myfile >> var3;
			myfile >> var4;
			cout << name << " " << var1 << " " << var2 << " " << var3 << " " << var4 << endl;
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

