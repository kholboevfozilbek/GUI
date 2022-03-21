

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <random>
#include "Board_Rect.h"
#include "Window_Rect.h"
#include "Buttons.h"
#include "User.h"

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
	bool user_quit = false;
	Window_Rect welcome;
	Window_Rect number_player_rect;
	Window_Rect level_rect;
	Window_Rect ask_symbol_rect;
	Button option_X;
	Button option_Y;

	int number_players=1; // by default single player
	int level=1;          // by default beginner mode
	
	User our_single_user;

	User player1;
	User player2;

	std::random_device rd;
	
	Window_Rect win_draw;
	Button winner_announce;
	Window_Rect exit;

public:

	Tic_Tac_Toe();
	void Initialise();
	void generate_the_board();
	void display_board();

	void Execute();
	void Event_Handler(SDL_Event& event);
	void Render();

	void render_welcome();
	void render_information_specs();
	void render_ask_symbol_rect();
	void render_optionX();
	void render_optionY();
	void render_exit();

	void ask_single_user_symbol();
	void listen_user_symbol_input();
	void listen_user_game_input();
	
	bool win();
	bool wait_user_exit_win();
	bool draw();
	bool wait_user_exit_draw();


	void set_player_level(int number, int lev)
	{
		number_players = number;
		level = lev;
	}

	void single_player_game();
	void single_player_mode();
	void beginner_level_game();
	void basic_level_game();
	void hard_level_game();

	void rowwise_block();
	bool first_row_check_block();
	bool second_row_check_block();
	bool third_row_check_block();
	void columnwise_block();
	bool first_column_check_block();
	bool second_column_check_block();
	bool third_column_check_block();
	void diagonally_block();
	bool first_diagonal_check_block();
	bool second_diagonal_check_block();

	
};

