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

