

#include <iostream>
#include <SDL.h>

using namespace std;

int main(int argc, char* args[])
{
	//create window pointer, like data type
	SDL_Window* window = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "\nSDL could not be initialised " << SDL_GetError() << endl;
	else
		cout << "\n\nSDL video system is ready to go " << endl;

	window = SDL_CreateWindow(
		"An SDL2 window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	
	if (window == NULL)
	{
		cout << "\n\nWindow could not be created " << endl;
		return -1;
	}

	bool game_running = true;
	while (game_running)
	{
		SDL_Event event;
		//start out event loop
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				game_running = false;
		}
	}
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}