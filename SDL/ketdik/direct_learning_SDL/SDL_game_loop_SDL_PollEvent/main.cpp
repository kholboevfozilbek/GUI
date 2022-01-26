
#include <iostream>
#include <stdexcept>
#include <SDL.h>

using namespace std;

//window screen dimensions -> needs to be constant
const int WIDTH = 640;
const int HEIGHT = 480;

int main(int argc, char* args[])
{
	/// INITIALISATION PART

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cout << "Could not initialise SDL2: -> " << SDL_GetError() << endl;
	cout << "\nSDL2 successfully initialised \n";

	//the window we will render to ...
	SDL_Window* window = nullptr;

	//surface contained by the window
	SDL_Surface* surface = nullptr;

	/// CREATION PART

	//create the window
	window = SDL_CreateWindow(
		"SDL2 game | application",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);

	if (window == NULL)
		cout << "\nWindow could not be created: -> " << SDL_GetError() << endl;
	cout << "\nWindow successfully created \n" << endl;

	//get window surface
	surface = SDL_GetWindowSurface(window);
	//fill surface background
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
	//Game Loop and SDL_PollEvent
	SDL_Event event;
	bool game_running = true;

	while (game_running)
	{
		//Event handling
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				game_running = false;
		}

		//update the surface
		SDL_UpdateWindowSurface(window);

	}

	

	/// CLEAN UP PART
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();


	return 0;
}