

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
	char placed_symbol;

public:

	Rectangle() = default;
	Rectangle(const SDL_Rect& rectangle)
	{
		own_rectangle.x = rectangle.x;
		own_rectangle.y = rectangle.y;
		own_rectangle.w = rectangle.w;
		own_rectangle.h = rectangle.h;
	}

	void set_dimensions(int x, int y, int w, int h)
	{
		this->own_rectangle.x = x;
		this->own_rectangle.y = y;
		this->own_rectangle.w = w;
		this->own_rectangle.h = h;
	}
	void set_empty(bool state) {
		empty = state;
	}
	void set_placedChar(char s) {
		placed_symbol = s;
	}

	void set_surface(const char* filepath, SDL_Renderer* renderer)
	{
		own_surface = SDL_LoadBMP(filepath);
		own_texture = SDL_CreateTextureFromSurface(renderer, own_surface);
	}

	const SDL_Rect* get_ownRect() {
		return &own_rectangle;
	}

	SDL_Texture* get_ownTexture() { return own_texture; }
	
	bool get_emptyness() { return empty;  }

	char get_placedChar() { return placed_symbol;  }
};