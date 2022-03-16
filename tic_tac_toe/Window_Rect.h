

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Board_Rect.h"
#include "Board_Rect.h"

using namespace std;

class Window_Rect : public Rectangle {

private:
	bool on_click = false;
	bool shown = false;

public:

	Window_Rect() = default;
	Window_Rect(int x, int y, int w, int h, const char * surface_file_path, SDL_Renderer* renderer)
	{
		
		this->own_rectangle.x = x;
		this->own_rectangle.y = y;
		this->own_rectangle.w = w;
		this->own_rectangle.h = h;

		own_surface = SDL_LoadBMP(surface_file_path);
		own_texture = SDL_CreateTextureFromSurface(renderer, own_surface);
	}

	void setALL(int x, int y, int w, int h, const char* surface_file_path, SDL_Renderer* renderer)
	{
		this->own_rectangle.x = x;
		this->own_rectangle.y = y;
		this->own_rectangle.w = w;
		this->own_rectangle.h = h;

		own_surface = SDL_LoadBMP(surface_file_path);
		own_texture = SDL_CreateTextureFromSurface(renderer, own_surface);
	}

	void set_dimensions(int x, int y, int w, int h)
	{
		this->own_rectangle.x = x;
		this->own_rectangle.y = y;
		this->own_rectangle.w = w;
		this->own_rectangle.h = h;
	}

	const SDL_Rect* get_ownRect() {
		return &own_rectangle;
	}

	SDL_Texture* get_ownTexture() { return own_texture;  }

	bool get_onclick() { return on_click;  }
	void set_onclick(bool state) { on_click = state; }

	bool get_shown() { return shown; }
	void set_shown(bool state) { shown = state; }
};
