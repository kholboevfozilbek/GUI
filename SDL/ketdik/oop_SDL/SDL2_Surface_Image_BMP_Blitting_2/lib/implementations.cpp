
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
	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
	return true;
}

void Game::Loop()
{
	while (game_running)
	{
		Render();
		SDL_UpdateWindowSurface(window);
	}
}

void Game::Render()
{
	BlitImage_Surface("assets/images/hottie.bmp", NULL, NULL);
}

void Game::Clean_Up()
{
	if (window)
		SDL_DestroyWindow(window);
	if (image)
		SDL_FreeSurface(image);
	SDL_Quit();
}