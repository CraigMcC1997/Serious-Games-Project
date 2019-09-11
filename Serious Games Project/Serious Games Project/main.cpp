#pragma once
#include <SDL.h>
#include <iostream>
#include "Mojito.h"
#include "Game.h"

Game game = Game();
void init()
{
	game.init();
}

void update(SDL_Event sdlEvent)
{

}

void draw()
{

}


int main(int argc, char* argv[])
{
	init();

	SDL_Event sdlEvent;	// variable to detect SDL events
	bool running = true;
	while (running)
	{	// the event loop
		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
				running = false;
		}
		update(sdlEvent);
		draw();
	}
	return 0;
}