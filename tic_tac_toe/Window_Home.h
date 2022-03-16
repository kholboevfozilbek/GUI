

#pragma once


#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Board_Rect.h"

using namespace std;


class Window_Home {

private:

	SDL_Rect welcome;
	SDL_Rect rules;
	SDL_Rect number_players;
	SDL_Rect level;

	TTF_Font* our_font = nullptr;

public:


};