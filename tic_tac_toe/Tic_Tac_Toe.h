

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Board_Rect.h"

using namespace std;

class Tic_Tac_Toe
{

private:

	Rectangle board_arr[3][3];

	const int WIDTH = 1200;
	const int HEIGHT = 650;
	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* our_font = nullptr;
	SDL_Surface* text_surface = nullptr;
	SDL_Texture* text_texture = nullptr;

	SDL_Event event;
	bool running = true;

	// home window part 
	bool game_started = false;
	SDL_Rect welcome;
	SDL_Rect rules;
	bool on_click = false;
	SDL_Rect list_rules;
	SDL_Rect number_players;
	SDL_Rect level;
	

public:

	Tic_Tac_Toe();

	void Execute();
	void Initialise();
	void Event_Handler(SDL_Event& event);
	void Render();
	void generate_the_board();

	//main window
	void generate_home_window();
	void handle_main_window_event();
	void mouse_press_for_drop_down(SDL_Event& event);
	void mouse_press_for_rules(SDL_Point mousePosition);
	void render_main_window();

};

