
#include "../include/game.h"
#include <iostream>
#include <stdexcept>

using namespace std;


Game::Game()
{
	initialization();
}

Game::~Game()
{
	Clean_Up();
}

bool Game::initialization()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	window = SDL_CreateWindow(
		"SDL2 game | application",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
	);

	if (window == NULL)
		return false;
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 7, 105, 11));
	return true;
}

void Game::Loop()
{
	while (game_running)
	{
		while (SDL_PollEvent(&event))
		{
			On_Event(event);
		}
		SDL_UpdateWindowSurface(window);
	}
}


void Game::On_Event(SDL_Event	event)
{
	if (event.type == SDL_QUIT)
		game_running = false;
}


void Game::Clean_Up()
{
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
}