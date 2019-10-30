#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "Window.h"
#include "Game.h"

//#if _DEBUG
//#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
//#endif


Game* game;
POINT mousePos;
Window* hWindow;
SDL_GLContext glContext; // OpenGL context handle

bool handleSDLEvent(SDL_Event const& sdlEvent)
{
	if (sdlEvent.type == SDL_QUIT)
		return false;
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		// Can extend this to handle a wider range of keys
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			return false;
		default:
			break;
		}
	}
	return true;
}

void exitFatalError(char* message)
{
	cout << message << " " << endl;
	cout << SDL_GetError();
	SDL_Quit();
	exit(1);
}

void init()
{
	game = new Game();
	game->init();
}

void update(SDL_Event sdlEvent)
{
	game->update(sdlEvent);

	GetCursorPos(&mousePos);	//tracking the mouse position
	

	if (mousePos.x > (hWindow->getXPos()) && mousePos.x < (hWindow->getXPos() + hWindow->getWidth()) &&		//checking if the mouse in in the window
		mousePos.y >(hWindow->getYPos()) && mousePos.y < (hWindow->getYPos() + hWindow->getHeight()))
	{
		game->mouseInput();	//checking for mouse inputs
	}
}

void draw(SDL_Window* window)
{
	game->draw(window);
}

void cleanUp()
{
	BASS_Free();
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(hWindow->getWindow());
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	
	SDL_Event sdlEvent;  // variable to detect SDL events
	SDL_Renderer* renderTarget = nullptr;

	hWindow = new Window(800, 600, "Serious Games Project"); // window handle

	hWindow->setupRC(glContext);
	renderTarget = SDL_CreateRenderer(hWindow->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) { // glewInit failed, something is seriously wrong
		std::cout << "glewInit failed, aborting." << endl;
		exit(1);
	}
	cout << glGetString(GL_VERSION) << endl;

	init();

	bool running = true;
	while (running)

	{	// the event loop
		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
				running = false;
		}
		update(sdlEvent);
		draw(hWindow->getWindow());
	}

	cleanUp();
	return 0;
}