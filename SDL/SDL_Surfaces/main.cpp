

#include <iostream>
#include <SDL.h>
#include <stdexcept>

using namespace std;

const int WIDTH = 640;
const int HIGHT = 480;

void which_key_pressed(SDL_Event event);
void which_mouse_button(SDL_Event event);
void SetPixel(SDL_Surface* screen, uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b, SDL_Event event);

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw runtime_error("\n\nSDL could not be initialised \n\n");
	
	SDL_Window* window;
	SDL_Event event;
	SDL_Surface* screen;
	SDL_Surface* image;

	

	window = SDL_CreateWindow(
		"Our application | game ",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);

	if (window == NULL)
		throw runtime_error("\n\nwindow could not be initialised \n\n");
	screen = SDL_GetWindowSurface(window);
	SDL_UpdateWindowSurface(window);

	
	bool game_running = true;
	while (game_running)
	{
		int x, y;
		Uint32 buttons;
		buttons = SDL_GetMouseState(&x, &y);
		while (SDL_PollEvent(&event))
		{
			/*switch (event.type)
			{
			case SDL_QUIT:
				game_running = false;
				break;
			case SDL_MOUSEMOTION:
				//cout << "mouse has been moved \n";
				break;
			case SDL_KEYDOWN:
				which_key_pressed(event);
				break;

			case SDL_MOUSEBUTTONDOWN:
				SetPixel(screen, x, y, 255, 0, 0, event);
				break;
			default:
				break;
			}*/
			if (event.type == SDL_QUIT)
				game_running = false;
			if (event.button.button == SDL_BUTTON_LEFT)
				SetPixel(screen, x, y, 255, 0, 0, event);
		}
		SDL_UpdateWindowSurface(window);
	}


	///CleanUps

	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}

void which_key_pressed(SDL_Event event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_0:
		cout << "0 was pressed \n";
		// the actions that should happen in the game when 0 pressed
		break;
	case SDLK_1:
		cout << "1 was pressed \n";
		// the actions that should happen in the game when 0 pressed
		break;
	case SDLK_2:
		cout << "2 was pressed \n";
		// the actions that should happen in the game when 0 pressed
		break;
	case SDLK_3:
		cout << "3 was pressed \n";
		// the actions that should happen in the game when 0 pressed
		break;
	case SDLK_4:
		cout << "4 was pressed \n";
		// the actions that should happen in the game when 0 pressed
		break;
	case SDLK_5:
		cout << "5 was pressed \n";
		// the actions that should happen in the game when 0 pressed
		break;
	case SDLK_6:
		cout << "6 was pressed \n";
		// the actions that should happen in the game when 0 pressed
		break; 
	case SDLK_7:
			cout << "7 was pressed \n";
			// the actions that should happen in the game when 0 pressed
			break;
	case SDLK_8:
		cout << "8 was pressed \n";
		// the actions that should happen in the game when 0 pressed
		break;
	case SDLK_9:
		cout << "9 was pressed \n";
		// the actions that should happen in the game when 0 pressed
		break;
	default:
		cout << "some key has been pressed \n";
		break;
	}
}

void which_mouse_button(SDL_Event event)
{
	switch (event.button.button)
	{
	case SDL_BUTTON_LEFT:
		cout << "left mouse button pressed " << endl;
		break;

	case SDL_BUTTON_RIGHT:
		cout << "right mouse button was pressed " << endl;
		break;
	case SDL_BUTTON_MIDDLE:
		cout << "middle mouse button was pressed " << endl;
		break;
	default:
		break;
	}
}

void SetPixel(SDL_Surface* screen, uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b, SDL_Event event)
{
	SDL_LockSurface(screen);
	which_mouse_button(event);
	cout << "(" << x << ", " << y << ")" << endl;
	uint8_t* pixelsArray = (uint8_t* )screen->pixels;
	pixelsArray[y * screen->pitch + x*screen->format->BytesPerPixel + 0] = b; // offset red
	pixelsArray[y * screen->pitch + x*screen->format->BytesPerPixel + 1] = g; // offset green
	pixelsArray[y * screen->pitch + x*screen->format->BytesPerPixel + 2] = r; // offset blue  
	SDL_UnlockSurface(screen);
}