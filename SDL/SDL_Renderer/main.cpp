
#include <iostream>
#include<stdexcept>
#include <SDL.h>
#include <vector>

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;

#define POINTS_COUNT 4

static SDL_Point points[POINTS_COUNT] = {
	{320, 200},
	{300, 240},
	{340, 240},
	{320, 200}
};

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw runtime_error("\nCoul not initialise the SDL!");
	
	SDL_Window* window = nullptr;

	window = SDL_CreateWindow(
		"Our application | game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);

	SDL_Point upside[2] = {
		{80, 60},
		{110, 60}
	};
	SDL_Point leftside[2] = {
		{80, 60},
		{80, 120}
	};
	SDL_Point rightside[2] = {
		{110, 60},
		{110, 120}
	};

	SDL_Point downside[2] = {
		{80, 120},
		{110, 120}
	};

	if (window == NULL)
		throw runtime_error("\nCould not create a window!");

	SDL_Renderer* renderer = nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		throw runtime_error("\nCould not associate renderer with current window!");


	bool game_running = true;



	while (game_running)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				game_running = false;

		}

		// (3) Clear and Draw the Screen
		//We cleaned the renderer
		//LET US GIVE OURSELVES BLACK BACKGROUND
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); 
		SDL_RenderClear(renderer);

		//Do our drawing here
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		//SDL_RenderDrawLine(renderer, 5, 5, 100, 120);
		SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
		//SDL_RenderDrawLines(renderer, letter_o, 6);
		SDL_RenderDrawLines(renderer, upside, 2);
		SDL_RenderDrawLines(renderer, leftside, 2);
		SDL_RenderDrawLines(renderer, rightside, 2);
		SDL_RenderDrawLines(renderer, downside, 2);

		

		//finally present what we have drawn!
		SDL_RenderPresent(renderer);
	}

	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);

	return 0;
}
