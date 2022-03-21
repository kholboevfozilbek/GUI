

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Board_Rect.h"
#include "Window_Rect.h"
#include "Buttons.h"
#include "Empty_Space.h"
using namespace std;

class Home_Window {

private:
	const int WIDTH = 1200;
	const int HEIGHT = 650;
	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* our_font = nullptr;
	SDL_Surface* text_surface = nullptr;
	SDL_Texture* text_texture = nullptr;

	SDL_Event event;

	bool game_started = false;
	
	Window_Rect welcome;
	Window_Rect rules;
	Window_Rect list_rules;
	Window_Rect number_players;
	Window_Rect single_player;
	Window_Rect multiple_player;
	Button for_single_player;
	Button for_multiple_player;
	Window_Rect level;

	Button for_beginner_level;
	Button for_basic_level;
	Button for_hard_level;

	Window_Rect rect_beginner_level;
	Window_Rect rect_basic_level;
	Window_Rect rect_hard_level;

	Window_Rect start;

	int user_chosen_level=1;
	int user_chosen_number_players = 1;
public:

	Home_Window();
	~Home_Window();
	void Initiliase();
	void Free_Resources();
	void Execute(int& number_players, int& level);
	void Event_Handler(SDL_Event& event);
	void Render();
	void render_welcome();
	void render_rules();
	void render_list_rules();
	void render_number_players();
	void render_level();
	void render_player_notes();
	void render_single_player_rect();
	void render_multiple_player_rect();
	void render_start();
	void put_tick();

	void render_levels();
	void put_tick_for_levels();

	void mouse_click_drop_down();
	void drop_down_for_rules(SDL_Point& mousePosition);
	void drop_down_for_number_players(SDL_Point&  mousePosition);
	void drop_down_for_level(SDL_Point& mousePosition);

	void user_input_number_players();
	void user_input_game_level();
};