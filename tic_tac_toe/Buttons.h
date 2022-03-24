

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
	SDL_Surface* own_surface = nullptr;
	SDL_Texture* own_texture = nullptr;

public:

	Button() = default;

	~Button()
	{
		SDL_FreeSurface(own_surface);
		SDL_DestroyTexture(own_texture);
	}

	void Free_Resources()
	{
		SDL_FreeSurface(own_surface);
		SDL_DestroyTexture(own_texture);
	}
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

	void reset_surface_texture(const char* filepath, SDL_Renderer* renderer)
	{
		if (this->own_surface != nullptr)
		{
			SDL_FreeSurface(this->own_surface);
			SDL_DestroyTexture(this->own_texture);
		}

		own_surface = SDL_LoadBMP(filepath);
		own_texture = SDL_CreateTextureFromSurface(renderer, own_surface);
	}
};