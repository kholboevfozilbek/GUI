

#pragma once


#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Board_Rect.h"
#include "Window_Rect.h"
using namespace std;

class Button {

private:

	SDL_Rect own_rectangle;
	bool active;
	SDL_Surface* own_surface;
	SDL_Texture* own_texture;

public:

	Button() = default;

	Button(int x, int y, int w, int h, bool active_state)
	{
		this->own_rectangle.x = x;
		this->own_rectangle.y = y;
		this->own_rectangle.w = w;
		this->own_rectangle.h = h;

		active = active_state; 
	}

	void setALL(int x, int y, int w, int h, bool active_state, const char* filepath, SDL_Renderer* renderer)
	{
		this->own_rectangle.x = x;
		this->own_rectangle.y = y;
		this->own_rectangle.w = w;
		this->own_rectangle.h = h;

		active = active_state;

		own_surface = SDL_LoadBMP(filepath);
		own_texture = SDL_CreateTextureFromSurface(renderer, own_surface);
	}

	void set_dimensions(int x, int y, int w, int h)
	{
		this->own_rectangle.x = x;
		this->own_rectangle.y = y;
		this->own_rectangle.w = w;
		this->own_rectangle.h = h;
	}

	void set_active_state(bool s) { active = s;  }

	bool get_active_state() { return active;  }

	SDL_Texture* get_ownTexture() { return own_texture; }

	const SDL_Rect* get_ownRect() {
		return &own_rectangle;
	}

	void set_surface(const char* filepath, SDL_Renderer* renderer)
	{
		own_surface = SDL_LoadBMP(filepath);
		own_texture = SDL_CreateTextureFromSurface(renderer, own_surface);
	}
};