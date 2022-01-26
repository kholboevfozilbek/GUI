
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
	const int WIDTH = 640;
	const int HEIGHT = 480;
	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;
	bool game_running = true;

public:
	Game();
	~Game();
	bool initialization();
	void Loop();
	void Render();
	void Clean_Up();

};



#endif // !GAME_H_KNOWN



