
#include <iostream>
#include<stdexcept>
#include <SDL.h>
#include <vector>

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;


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

	if (window == NULL)
		throw runtime_error("\nCould not create a window!");

	SDL_Renderer* renderer = nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* surf = SDL_LoadBMP("kong.bmp");
	SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 0, 255));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);

	if (renderer == NULL)
		throw runtime_error("\nCould not associate renderer with current window!");


	bool game_running = true;
	SDL_Rect rectangle;
	rectangle.x = 250;
	rectangle.y = 150;
	rectangle.w = 200;
	rectangle.h = 180;
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

		//SDL_RenderDrawRect(renderer, &rectangle);
		SDL_RenderCopy(renderer, texture, NULL, &rectangle);
		//finally present what we have drawn!
		SDL_RenderPresent(renderer);
	}

	if (texture)
		SDL_DestroyTexture(texture);

	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
