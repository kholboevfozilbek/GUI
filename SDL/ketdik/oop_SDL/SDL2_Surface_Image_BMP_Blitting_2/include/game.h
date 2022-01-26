
#pragma once
#ifndef GAME_H_KNOWN
#define GAME_H_KNOWN


#include <iostream>
#include <SDL.h>
#include <stdexcept>

using namespace std;

class Game
{
private:
	const int WIDTH = 1000;
	const int HEIGHT = 600;
	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Surface* image = nullptr;
	bool game_running = true;
	SDL_Rect* srect;
	SDL_Rect* drect;

public:
	Game();
	~Game();
	bool initialization();
	void Loop();
	void Render();
	void Clean_Up();
	void BlitImage_Surface(const char* image_path, SDL_Rect* srect, SDL_Rect* drect)
	{
		image = SDL_LoadBMP(image_path);
		SDL_BlitSurface(image, srect, surface, drect);
	}
	SDL_Rect getcoordinates_image();
};




#endif // !GAME_H_KNOWN



