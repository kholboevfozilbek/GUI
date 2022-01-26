
#include <SDL.h>
#include <stdio.h>
#include <iostream>

//screen dimention constants so window is fixed and not resizable
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	//the window we will be rendering to
	SDL_Window* window = NULL;

	//surface contained by the window
	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL  coun not intialise:  " <<  SDL_GetError();
	}
	else
	{
		//create the window
		window = SDL_CreateWindow("SDL tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
			std::cout << "Window could not be created " << SDL_GetError() << std::endl;
		else
		{
			//get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//fill surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//update surface
			SDL_UpdateWindowSurface(window);

			//wait 2 seconds
			SDL_Delay(2000);
		}
	
	}

	//SDL destroy the window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems

	SDL_Quit();

	return 0;
}