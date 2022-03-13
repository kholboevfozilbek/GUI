
#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdexcept>

using namespace std;


class Tic_Tac_Toe {

private:

	SDL_Rect arr[3][3]; // board
	SDL_Surface* arr_surfaces[3][3]; // board surfaces
	SDL_Texture* arr_textures[3][3]; // board textures

public:

	Tic_Tac_Toe();

};