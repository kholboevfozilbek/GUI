

#pragma once


#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

class Rectangle {

protected:

	SDL_Rect own_rectangle;
	SDL_Surface* own_surface = nullptr;
	SDL_Texture* own_texture = nullptr;
	bool empty = true;

public:

	Rectangle() = default;
	Rectangle(const SDL_Rect& rectangle)
	{
		own_rectangle.x = rectangle.x;
		own_rectangle.y = rectangle.y;
		own_rectangle.w = rectangle.w;
		own_rectangle.h = rectangle.h;
	}
};