
#include "Tic_Tac_Toe.h"
#include <string>
#include <list>
#include "Empty_Space.h"

using namespace std;

Tic_Tac_Toe::Tic_Tac_Toe()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw std::runtime_error("Could not initialise SDL2 ");
	std::cout << "\nSDL2 successfully initialised \n";

	if (TTF_Init() == -1)
		std::cout << "Could not initialise TTF:  -> " << TTF_GetError() << std::endl;
	std::cout << "SDL TTF has successfully initialised" << std::endl;

	
}

void Tic_Tac_Toe::Initialise()
{
	window = SDL_CreateWindow(
		"Tic Tac Toe",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);

	if (window == NULL)
		std::cout << "\nWindow could not be created: -> " << SDL_GetError() << std::endl;
	std::cout << "\nWindow successfully created \n" << std::endl;
	
	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		throw std::runtime_error("\nCould not associate renderer with current window!");

	our_font = TTF_OpenFont("fonts/DebugFreeTrial-MVdYB.otf", 25);
	if (our_font == nullptr) {
		std::cout << "Could not load the font" << std::endl;
	}

	welcome.set_dimensions(400, 20, 400, 50);

	number_player_rect.set_dimensions(400, 90, 130, 30);
	level_rect.set_dimensions(400, 130, 130, 30);

	ask_symbol_rect.set_dimensions(400, 20, 400, 50);
	option_X.set_dimensions(450, 90, 20, 20);
	option_X.set_surface("assets/images/x.bmp", renderer);
	option_Y.set_dimensions(500, 90, 20, 20);

	win_draw.set_dimensions(850, 230, 100, 50);
	winner_announce.set_dimensions(870, 300, 30, 30);
	exit.set_dimensions(900, 570, 50, 20);

	generate_the_board();
}

void Tic_Tac_Toe::generate_the_board()
{
	
	board_arr[0][0].set_dimensions(400, 200, 130, 130);
	int x = 530, y = 200, w = 130, h = 130;

	for (int j = 1; j < 3; ++j)
	{
		board_arr[0][j].set_dimensions(x, y, w, h);
		x = x + w;
	}

	x = 400, y = 330, w = 130, h = 130;

	for (int j = 0; j < 3; ++j)
	{
		board_arr[1][j].set_dimensions(x, y, w, h);
		x = x + w;
	}

	x = 400, y = 460, w = 130, h = 130;

	for (int j = 0; j < 3; ++j)
	{
		board_arr[2][j].set_dimensions(x, y, w, h);
		x = x + w;
	}
}



void Tic_Tac_Toe::Execute()
{
	Initialise();

	if (number_players == 1)
		ask_single_user_symbol();

	SDL_RenderClear(renderer);
	while (running)
	{
		Event_Handler(event);

		if (win() == true)
		{
			if(wait_user_exit_win() == true)
				break;
		}
		else if (draw() == true)
		{
			if (wait_user_exit_draw() == true)
				break;
		}
			
		if (number_players == 1) // lets handle single player mode first
			single_player_game();
			
		Render();
	}
}

void Tic_Tac_Toe::Event_Handler(SDL_Event& event)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			running = false;
	}

}

void Tic_Tac_Toe::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	render_welcome();
	render_information_specs();

	display_board();

	SDL_RenderPresent(renderer);
}



void Tic_Tac_Toe::display_board()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < 3; ++i)
	{
		for(int j=0; j<3; ++j)
			SDL_RenderDrawRect(renderer, board_arr[i][j].get_ownRect());
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Tic_Tac_Toe::render_welcome()
{
	text_surface = TTF_RenderText_Solid(our_font, "Welcome to Tic Tac Toe Game!", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, welcome.get_ownRect());
}

void Tic_Tac_Toe::render_exit()
{
	text_surface = TTF_RenderText_Solid(our_font, "Exit", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, exit.get_ownRect());
}

void Tic_Tac_Toe::render_information_specs()
{
	string mode;
	string level_print;
	if (number_players < 2)
		mode = "Mode  Single Player";
	else
		mode = "Mode  Multiple Player";

	switch (level)
	{
	case 1 :
		level_print = "Level  Beginner";
		break;
	case 2:
		level_print = "Level  Basic";
		break;
	case 3:
		level_print = "Level  Hard";
		break;
	default:
		break;
	}
		

	text_surface = TTF_RenderText_Solid(our_font, mode.c_str(), { 255, 0, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, number_player_rect.get_ownRect());


	text_surface = TTF_RenderText_Solid(our_font, level_print.c_str(), { 255, 0, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, level_rect.get_ownRect());
}

void Tic_Tac_Toe::render_ask_symbol_rect()
{
	text_surface = TTF_RenderText_Solid(our_font, "Choose a symbol", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, ask_symbol_rect.get_ownRect());
}

void Tic_Tac_Toe::render_optionX()
{
	text_surface = TTF_RenderText_Solid(our_font, "X", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, option_X.get_ownRect());
}

void Tic_Tac_Toe::render_optionY()
{
	text_surface = TTF_RenderText_Solid(our_font, "O", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, option_Y.get_ownRect());
}




void Tic_Tac_Toe::ask_single_user_symbol()
{
	while (our_single_user.get_symbol() == '\0')
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		render_ask_symbol_rect();
		render_optionX();
		render_optionY();
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				break;
			}
		}
		listen_user_symbol_input();
		SDL_RenderPresent(renderer);
	}
}

void Tic_Tac_Toe::listen_user_symbol_input()
{
	SDL_Point mousePosition;
	mousePosition.x = event.motion.x;
	mousePosition.y = event.motion.y;

	if (SDL_PointInRect(&mousePosition, option_X.get_ownRect()))
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			if (number_players == 1)
			{
				our_single_user.set_symbol('X');
				cout << "\nX has been captured" << endl;
				our_single_user.set_turn(true);
			}
			else
			{
				player1.set_symbol('X');
				player2.set_symbol('O');

			}
		}
	}
	else if (SDL_PointInRect(&mousePosition, option_Y.get_ownRect()))
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			if (number_players == 1)
			{
				our_single_user.set_symbol('O');
				cout << "\nO has been captured" << endl;
				our_single_user.set_turn(true);
			}
			else
			{
				player1.set_symbol('O');
				player2.set_symbol('X');
			}
		}
	}

}

void Tic_Tac_Toe::listen_user_game_input()
{
	SDL_Point mousePosition;

	mousePosition.x = event.motion.x;
	mousePosition.y = event.motion.y;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (SDL_PointInRect(&mousePosition, board_arr[i][j].get_ownRect()))
			{
				if (board_arr[i][j].get_emptyness() == true)
				{
					if (event.button.type == SDL_MOUSEBUTTONDOWN)
					{
						switch (our_single_user.get_symbol())
						{
						case 'X':
							board_arr[i][j].set_surface("assets/images/x.bmp", renderer);
							SDL_RenderCopy(renderer, board_arr[i][j].get_ownTexture(), NULL, board_arr[i][j].get_ownRect());
							board_arr[i][j].set_empty(false);
							board_arr[i][j].set_placedChar('X');
							our_single_user.set_turn(false);
							break;
						case 'O':
							board_arr[i][j].set_surface("assets/images/o.bmp", renderer);
							SDL_RenderCopy(renderer, board_arr[i][j].get_ownTexture(), NULL, board_arr[i][j].get_ownRect());
							board_arr[i][j].set_empty(false);
							board_arr[i][j].set_placedChar('O');
							our_single_user.set_turn(false);
							break;
						default:
							break;
						}
					}

				}
			}
		}
	}
}



bool Tic_Tac_Toe::win()
{
	//first row win? check
	if (board_arr[0][0].get_placedChar() != '\0')
	{
		if (board_arr[0][0].get_placedChar() == board_arr[0][1].get_placedChar() && board_arr[0][1].get_placedChar() == board_arr[0][2].get_placedChar())
		{
			text_surface = TTF_RenderText_Solid(our_font, "Winner!", { 0, 255, 0 });
			text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
			SDL_RenderCopy(renderer, text_texture, NULL, win_draw.get_ownRect());

			if (board_arr[0][0].get_placedChar() == 'X')
				winner_announce.set_surface("assets/images/x.bmp", renderer);
			else
				winner_announce.set_surface("assets/images/o.bmp", renderer);
			SDL_RenderCopy(renderer, winner_announce.get_ownTexture(), NULL, winner_announce.get_ownRect());

			running = false;
			std::cout << "first row win has been captured" << endl;
			return true;
		
		}

	}

	// second row win? check
	if (board_arr[1][0].get_placedChar() != '\0')
	if (board_arr[1][0].get_placedChar() == board_arr[1][1].get_placedChar() && board_arr[1][1].get_placedChar() == board_arr[1][2].get_placedChar())
	{
		text_surface = TTF_RenderText_Solid(our_font, "Winner!", { 0, 255, 0 });
		text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		SDL_RenderCopy(renderer, text_texture, NULL, win_draw.get_ownRect());

		if (board_arr[1][0].get_placedChar() == 'X')
			winner_announce.set_surface("assets/images/x.bmp", renderer);
		else
			winner_announce.set_surface("assets/images/o.bmp", renderer);
		SDL_RenderCopy(renderer, winner_announce.get_ownTexture(), NULL, winner_announce.get_ownRect());

		running = false;
		cout << "second row win has been captured" << endl;
		return true;
	}

	// third row win? check
	if (board_arr[2][0].get_placedChar() != '\0')
	if (board_arr[2][0].get_placedChar() == board_arr[2][1].get_placedChar() && board_arr[2][1].get_placedChar() == board_arr[2][2].get_placedChar())
	{
		text_surface = TTF_RenderText_Solid(our_font, "Winner!", { 0, 255, 0 });
		text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		SDL_RenderCopy(renderer, text_texture, NULL, win_draw.get_ownRect());

		if (board_arr[2][0].get_placedChar() == 'X')
			winner_announce.set_surface("assets/images/x.bmp", renderer);
		else
			winner_announce.set_surface("assets/images/o.bmp", renderer);
		SDL_RenderCopy(renderer, winner_announce.get_ownTexture(), NULL, winner_announce.get_ownRect());

		running = false;
		cout << "3 row win has been captured" << endl;
		return true;
	}

	// cols

	//first column win? check
	if (board_arr[0][0].get_placedChar() != '\0')
	if (board_arr[0][0].get_placedChar() == board_arr[1][0].get_placedChar() && board_arr[1][0].get_placedChar() == board_arr[2][0].get_placedChar())
	{
		text_surface = TTF_RenderText_Solid(our_font, "Winner!", { 0, 255, 0 });
		text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		SDL_RenderCopy(renderer, text_texture, NULL, win_draw.get_ownRect());

		if (board_arr[0][0].get_placedChar() == 'X')
			winner_announce.set_surface("assets/images/x.bmp", renderer);
		else
			winner_announce.set_surface("assets/images/o.bmp", renderer);
		SDL_RenderCopy(renderer, winner_announce.get_ownTexture(), NULL, winner_announce.get_ownRect());

		running = false;
		cout << "first column win has been captured" << endl;
		return true;
	}

	//second column win? check
	if (board_arr[0][1].get_placedChar() != '\0')
	if (board_arr[0][1].get_placedChar() == board_arr[1][1].get_placedChar() && board_arr[1][1].get_placedChar() == board_arr[2][1].get_placedChar())
	{
		text_surface = TTF_RenderText_Solid(our_font, "Winner!", { 0, 255, 0 });
		text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		SDL_RenderCopy(renderer, text_texture, NULL, win_draw.get_ownRect());

		if (board_arr[0][1].get_placedChar() == 'X')
			winner_announce.set_surface("assets/images/x.bmp", renderer);
		else
			winner_announce.set_surface("assets/images/o.bmp", renderer);
		SDL_RenderCopy(renderer, winner_announce.get_ownTexture(), NULL, winner_announce.get_ownRect());

		running = false;
		cout << "second column win has been captured" << endl;
		return true;
	}

	//third column win? check
	if (board_arr[0][2].get_placedChar() != '\0')
	if (board_arr[0][2].get_placedChar() == board_arr[1][2].get_placedChar() && board_arr[1][2].get_placedChar() == board_arr[2][2].get_placedChar())
	{
		text_surface = TTF_RenderText_Solid(our_font, "Winner!", { 0, 255, 0 });
		text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		SDL_RenderCopy(renderer, text_texture, NULL, win_draw.get_ownRect());

		if (board_arr[0][2].get_placedChar() == 'X')
			winner_announce.set_surface("assets/images/x.bmp", renderer);
		else
			winner_announce.set_surface("assets/images/o.bmp", renderer);
		SDL_RenderCopy(renderer, winner_announce.get_ownTexture(), NULL, winner_announce.get_ownRect());

		running = false;
		cout << "third column win has been captured" << endl;
		return true;
	}

	//diagonal win? check

	//first diagonal
	if (board_arr[0][0].get_placedChar() != '\0')
	{
		if (board_arr[0][0].get_placedChar() == board_arr[1][1].get_placedChar() && board_arr[1][1].get_placedChar() == board_arr[2][2].get_placedChar())
		{
			text_surface = TTF_RenderText_Solid(our_font, "Winner!", { 0, 255, 0 });
			text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
			SDL_RenderCopy(renderer, text_texture, NULL, win_draw.get_ownRect());

			if (board_arr[0][0].get_placedChar() == 'X')
				winner_announce.set_surface("assets/images/x.bmp", renderer);
			else
				winner_announce.set_surface("assets/images/o.bmp", renderer);
			SDL_RenderCopy(renderer, winner_announce.get_ownTexture(), NULL, winner_announce.get_ownRect());

			running = false;
			cout << "first diagonal win has been captured" << endl;
			return true;
		}
	}

	//second diagonal
	if (board_arr[0][2].get_placedChar() != '\0')
	{
		if (board_arr[0][2].get_placedChar() == board_arr[1][1].get_placedChar() && board_arr[1][1].get_placedChar() == board_arr[2][0].get_placedChar())
		{
			text_surface = TTF_RenderText_Solid(our_font, "Winner!", { 0, 255, 0 });
			text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
			SDL_RenderCopy(renderer, text_texture, NULL, win_draw.get_ownRect());

			if (board_arr[2][0].get_placedChar() == 'X')
				winner_announce.set_surface("assets/images/x.bmp", renderer);
			else
				winner_announce.set_surface("assets/images/o.bmp", renderer);
			SDL_RenderCopy(renderer, winner_announce.get_ownTexture(), NULL, winner_announce.get_ownRect());

			running = false;
			cout << "second diagonal win has been captured" << endl;
			return true;
		}
	}

}

bool Tic_Tac_Toe::wait_user_exit_win()
{
	while (true)
	{
		Event_Handler(event);
		SDL_Point mousePosition;
		mousePosition.x = event.motion.x;
		mousePosition.y = event.motion.y;

		if (SDL_PointInRect(&mousePosition, exit.get_ownRect()))
		{
			if (event.button.type == SDL_MOUSEBUTTONDOWN)
			{
				return true;
			}
		}
		render_exit();
		Render();
	}
}

bool Tic_Tac_Toe::draw()
{
	bool not_full = false;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (board_arr[i][j].get_emptyness() == true)
			{
				not_full = true;
			}
		}
	}

	if (not_full == true)
	{
		return false;	 // there is still space
	}
	else
	{
		text_surface = TTF_RenderText_Solid(our_font, "Draw!", { 0, 255, 0 });
		text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		SDL_RenderCopy(renderer, text_texture, NULL, win_draw.get_ownRect());
		return true; // if all space is full and no win it is a draw
	}
}

bool Tic_Tac_Toe::wait_user_exit_draw()
{
	while (true)
	{
		Event_Handler(event);
		SDL_Point mousePosition;
		mousePosition.x = event.motion.x;
		mousePosition.y = event.motion.y;

		if (SDL_PointInRect(&mousePosition, exit.get_ownRect()))
		{
			if (event.button.type == SDL_MOUSEBUTTONDOWN)
			{
				return true;
			}
		}
		render_exit();
		Render();
	}
}




void Tic_Tac_Toe::single_player_game()
{
	if (our_single_user.get_turn() == true) // in user turn we ask a place to enter 
	{
		listen_user_game_input();
	}
	else // in AI turn we look for level of the game and play accordingly
	{
		single_player_mode();
	}
}

void Tic_Tac_Toe::single_player_mode()
{
	switch (level) // level only matters in single player mode only
	{
	case 1: // 1 beginner level
		beginner_level_game();
		break;
	case 2:
		basic_level_game();
		break;
	case 3:
		//hard_level_game();
		break;
	default:
		break;
	}
}

void Tic_Tac_Toe::beginner_level_game()
{
	/*
	* beginner level only able to block rowwise 
	* so we check all 3 rows if there is near win situation if yes we should block it.
	* I think we better create reusale function that we can use later(higher) levels
	*/
	rowwise_block();
	// I make sure that in AI's turn it will surely fill one position
	our_single_user.set_turn(true);
}

void Tic_Tac_Toe::basic_level_game()
{
	/*
	*		basic level we are able to block rowwise  AND COLUMNWISE
	*		so we check all 3 rows if there is near win situation if yes we should block it.
	*/
	
	bool one_place_filled = false;
	/*
			so we check all 3 rows if there is near win situation if yes we should block it.
			we gonna place opposite symbol to users
	*/
	one_place_filled = first_row_check_block();

	//		if no place has been filled by first_row_check then we go for second row

	if (one_place_filled == false)
	{
		one_place_filled = second_row_check_block();
		if (one_place_filled == false)
		{
			one_place_filled = third_row_check_block();
		}
	}

	//		IF STILL NO PLACE HAS BEEN FILLED ADDITIONALLY WE LOOK FOR COLUMNS
	
	if(one_place_filled == false)
		columnwise_block();

	// I make sure that in AI's turn it will surely fill one position
	our_single_user.set_turn(true);
}


void Tic_Tac_Toe::rowwise_block()
{
	bool one_place_filled = false;
	/*
	so we check all 3 rows if there is near win situation if yes we should block it.
	we gonna place opposite symbol to users
	*/
	one_place_filled = first_row_check_block();
	// if no place has been filled by first_row_check then we go for second row

	if (one_place_filled == false)
	{
		one_place_filled = second_row_check_block();
		if (one_place_filled == false)
		{
			one_place_filled = third_row_check_block();
		}
	}


	// if still no place has been filled, may happen at the beginning of the game we
	// go and find list of empty spaces and randomly place one value

	if (one_place_filled == false)
	{
		std::list<Empty_Space> list_empty_spaces;
		int x;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (board_arr[i][j].get_emptyness() == true)
				{
					list_empty_spaces.push_back(Empty_Space(i, j));
				}
			}
		}

		// I need to generate one random number x = from 0 to list_empty_spaces.size() - 1;
		std:mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, list_empty_spaces.size() - 1);

		x = dist(gen);


		if (our_single_user.get_symbol() == 'X')
		{
			int i = 0;
			for (auto it = list_empty_spaces.begin(); it != list_empty_spaces.end(); ++it)
			{
				if (i == x)
				{
					board_arr[(*it).i][(*it).j].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[(*it).i][(*it).j].get_ownTexture(), NULL, board_arr[(*it).i][(*it).j].get_ownRect());
					board_arr[(*it).i][(*it).j].set_placedChar('O');
					board_arr[(*it).i][(*it).j].set_empty(false);

					cout << "\nboard_arr " << "  " << (*it).i << "  " << (*it).j << endl;
				}

				++i;
			}
		}
		else
		{
			int i = 0;
			for (auto it = list_empty_spaces.begin(); it != list_empty_spaces.end(); ++it)
			{
				if (i == x)
				{
					board_arr[(*it).i][(*it).j].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[(*it).i][(*it).j].get_ownTexture(), NULL, board_arr[(*it).i][(*it).j].get_ownRect());
					board_arr[(*it).i][(*it).j].set_placedChar('X');
					board_arr[(*it).i][(*it).j].set_empty(false);
				}

				++i;
			}
		}
	}
	
}

void Tic_Tac_Toe::columnwise_block()
{
	bool one_place_filled = false;

	one_place_filled = first_column_check_block();

	if (one_place_filled == false)
	{
		one_place_filled = second_column_check_block();

		if (one_place_filled == false)
		{
			one_place_filled = third_column_check_block();
		}
	}

	// if still no place has been filled, may happen at the beginning of the game we
	// go and find list of empty spaces and randomly place one value

	if (one_place_filled == false)
	{
		std::list<Empty_Space> list_empty_spaces;
		int x;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (board_arr[i][j].get_emptyness() == true)
				{
					list_empty_spaces.push_back(Empty_Space(i, j));
				}
			}
		}

		// I need to generate one random number x = from 0 to list_empty_spaces.size() - 1;
		std:mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, list_empty_spaces.size() - 1);

		x = dist(gen);

		if (our_single_user.get_symbol() == 'X')
		{
			int i = 0;
			for (auto it = list_empty_spaces.begin(); it != list_empty_spaces.end(); ++it)
			{
				if (i == x)
				{
					board_arr[(*it).i][(*it).j].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[(*it).i][(*it).j].get_ownTexture(), NULL, board_arr[(*it).i][(*it).j].get_ownRect());
					board_arr[(*it).i][(*it).j].set_placedChar('O');
					board_arr[(*it).i][(*it).j].set_empty(false);

					cout << "\nboard_arr " << "  " << (*it).i << "  " << (*it).j << endl;
				}

				++i;
			}
		}
		else
		{
			int i = 0;
			for (auto it = list_empty_spaces.begin(); it != list_empty_spaces.end(); ++it)
			{
				if (i == x)
				{
					board_arr[(*it).i][(*it).j].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[(*it).i][(*it).j].get_ownTexture(), NULL, board_arr[(*it).i][(*it).j].get_ownRect());
					board_arr[(*it).i][(*it).j].set_placedChar('X');
					board_arr[(*it).i][(*it).j].set_empty(false);
				}

				++i;
			}
		}
	}
}

bool Tic_Tac_Toe::first_row_check_block()
{
	//first check on top row
	// *  *  x
	if (board_arr[0][0].get_placedChar() == board_arr[0][1].get_placedChar())
	{
		if (board_arr[0][2].get_emptyness() == true)
		{
			switch (board_arr[0][1].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[0][2].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][2].get_ownTexture(), NULL, board_arr[0][2].get_ownRect());
					board_arr[0][2].set_empty(false);
					board_arr[0][2].set_placedChar('O');
					return true; // one place has been filled, and on one turn I can fill only one place 
					break;

				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[0][2].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][2].get_ownTexture(), NULL, board_arr[0][2].get_ownRect());
					board_arr[0][2].set_empty(false);
					board_arr[0][2].set_placedChar('X');
					return true;  // one place has been filled, and on one turn I can fill only one place
					break;
				}
				break;
			default:
				break;
			}
		}
		// if this  -  -  > combination does not work it is too early to return false we have to check other combinations as well 
	}

	// x  *   *
	if (board_arr[0][2].get_placedChar() == board_arr[0][1].get_placedChar())
	{
		if (board_arr[0][0].get_emptyness() == true)
		{
			switch (board_arr[0][1].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[0][0].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][0].get_ownTexture(), NULL, board_arr[0][0].get_ownRect());
					board_arr[0][0].set_empty(false);
					board_arr[0][0].set_placedChar('O');
					return true;
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[0][0].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][0].get_ownTexture(), NULL, board_arr[0][0].get_ownRect());
					board_arr[0][0].set_empty(false);
					board_arr[0][0].set_placedChar('X');
					return true;
					break;
				}
				break;
			default:
				break;
			}
		}
	}

	// *    x   *
	if (board_arr[0][2].get_placedChar() == board_arr[0][0].get_placedChar())
	{
		if (board_arr[0][1].get_emptyness() == true)
		{
			switch (board_arr[0][0].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[0][1].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][1].get_ownTexture(), NULL, board_arr[0][1].get_ownRect());
					board_arr[0][1].set_empty(false);
					board_arr[0][1].set_placedChar('O');
					return true;
					break;

				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[0][1].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][1].get_ownTexture(), NULL, board_arr[0][1].get_ownRect());
					board_arr[0][1].set_empty(false);
					board_arr[0][1].set_placedChar('X');
					return true;
					break;
				}
				break;
			default:
				break;
			}
		}
	}

	// if no combination works we have to let upper rowwise check know that from first row no place has been filled 
	// such that we go for second row

	return false;
}

bool Tic_Tac_Toe::second_row_check_block()
{
	//second check on second row

	// *   *   x
	if (board_arr[1][0].get_placedChar() == board_arr[1][1].get_placedChar())
	{
		if (board_arr[1][2].get_emptyness() == true)
		{
			switch (board_arr[1][1].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[1][2].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[1][2].get_ownTexture(), NULL, board_arr[1][2].get_ownRect());
					board_arr[1][2].set_empty(false);
					board_arr[1][2].set_placedChar('O');
					return true;
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[1][2].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[1][2].get_ownTexture(), NULL, board_arr[1][2].get_ownRect());
					board_arr[1][2].set_empty(false);
					board_arr[1][2].set_placedChar('X');
					return true;
					break;
				}
				break;
			default:
				break;
			}

		}
	}

	// x  *   *
	if (board_arr[1][2].get_placedChar() == board_arr[1][1].get_placedChar())
	{
		if (board_arr[1][0].get_emptyness() == true)
		{
			switch (board_arr[1][1].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[1][0].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[1][0].get_ownTexture(), NULL, board_arr[1][0].get_ownRect());
					board_arr[1][0].set_empty(false);
					board_arr[1][0].set_placedChar('O');
					return true;
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[1][0].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[1][0].get_ownTexture(), NULL, board_arr[1][0].get_ownRect());
					board_arr[1][0].set_empty(false);
					board_arr[1][0].set_placedChar('X');
					return true;
					break;
				}
				break;
			default:
				break;
			}
		}
	}

	// *    x   *
	if (board_arr[1][2].get_placedChar() == board_arr[1][0].get_placedChar())
	{
		if (board_arr[1][1].get_emptyness() == true)
		{
			switch (board_arr[1][0].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[1][1].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[1][1].get_ownTexture(), NULL, board_arr[1][1].get_ownRect());
					board_arr[1][1].set_empty(false);
					board_arr[1][1].set_placedChar('O');
					return true;
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[1][1].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[1][1].get_ownTexture(), NULL, board_arr[1][1].get_ownRect());
					board_arr[1][1].set_empty(false);
					board_arr[1][1].set_placedChar('X');
					return true;
					break;
				}
				break;
			default:
				break;
			}
		}
	}

	return false;
}

bool Tic_Tac_Toe::third_row_check_block()
{
	//third check on third row

	// *   *   x
	if (board_arr[2][0].get_placedChar() == board_arr[2][1].get_placedChar())
	{
		if (board_arr[2][2].get_emptyness() == true)
		{
			switch (board_arr[2][1].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				board_arr[2][2].set_surface("assets/images/o.bmp", renderer);
				SDL_RenderCopy(renderer, board_arr[2][2].get_ownTexture(), NULL, board_arr[2][2].get_ownRect());
				board_arr[2][2].set_empty(false);
				board_arr[2][2].set_placedChar('O');
				return true;
				break;
			case 'O':
				board_arr[2][2].set_surface("assets/images/x.bmp", renderer);
				SDL_RenderCopy(renderer, board_arr[2][2].get_ownTexture(), NULL, board_arr[2][2].get_ownRect());
				board_arr[2][2].set_empty(false);
				board_arr[2][2].set_placedChar('X');
				return true;
				break;
			default:
				break;
			}

		}
	}

	// x  *   *
	if (board_arr[2][2].get_placedChar() == board_arr[2][1].get_placedChar())
	{
		if (board_arr[2][0].get_emptyness() == true)
		{
			switch (board_arr[2][1].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				board_arr[2][0].set_surface("assets/images/o.bmp", renderer);
				SDL_RenderCopy(renderer, board_arr[2][0].get_ownTexture(), NULL, board_arr[2][0].get_ownRect());
				board_arr[2][0].set_empty(false);
				board_arr[2][0].set_placedChar('O');
				return true;
				break;
			case 'O':
				board_arr[2][0].set_surface("assets/images/x.bmp", renderer);
				SDL_RenderCopy(renderer, board_arr[2][0].get_ownTexture(), NULL, board_arr[2][0].get_ownRect());
				board_arr[2][0].set_empty(false);
				board_arr[2][0].set_placedChar('X');
				return true;
				break;
			default:
				break;
			}

		}
	}

	// *    x   *
	if (board_arr[2][2].get_placedChar() == board_arr[2][0].get_placedChar())
	{
		if (board_arr[2][1].get_emptyness() == true)
		{
			switch (board_arr[2][0].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				board_arr[2][1].set_surface("assets/images/o.bmp", renderer);
				SDL_RenderCopy(renderer, board_arr[2][1].get_ownTexture(), NULL, board_arr[2][1].get_ownRect());
				board_arr[2][1].set_empty(false);
				board_arr[2][1].set_placedChar('O');
				return true;
				break;
			case 'O':
				board_arr[2][1].set_surface("assets/images/x.bmp", renderer);
				SDL_RenderCopy(renderer, board_arr[2][1].get_ownTexture(), NULL, board_arr[2][1].get_ownRect());
				board_arr[2][1].set_empty(false);
				board_arr[2][1].set_placedChar('X');
				return true;
				break;
			default:
				break;
			}

		}
	}

	return false;
}

bool Tic_Tac_Toe::first_column_check_block()
{
	/*    *
		  *
		  x
	*/

	//first check on left column
	if (board_arr[0][0].get_placedChar() == board_arr[1][0].get_placedChar())
	{
		if (board_arr[2][0].get_emptyness() == true)
		{
			switch (board_arr[1][0].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[2][0].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[2][0].get_ownTexture(), NULL, board_arr[2][0].get_ownRect());
					board_arr[2][0].set_empty(false);
					board_arr[2][0].set_placedChar('O');
					return true; // one place has been filled, and on one turn I can fill only one place 
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[2][0].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[2][0].get_ownTexture(), NULL, board_arr[2][0].get_ownRect());
					board_arr[2][0].set_empty(false);
					board_arr[2][0].set_placedChar('X');
					return true;  // one place has been filled, and on one turn I can fill only one place
					break;
				}
				break;
			default:
				break;
			}
		}
		// if this  -  -  > combination does not work it is too early to return false we have to check other combinations as well 
	}

	/*    x
		  *
		  *
	*/

	if (board_arr[2][0].get_placedChar() == board_arr[1][0].get_placedChar())
	{
		if (board_arr[0][0].get_emptyness() == true)
		{
			switch (board_arr[1][0].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[0][0].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][0].get_ownTexture(), NULL, board_arr[0][0].get_ownRect());
					board_arr[0][0].set_empty(false);
					board_arr[0][0].set_placedChar('O');
					return true; // one place has been filled, and on one turn I can fill only one place 
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[0][0].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][0].get_ownTexture(), NULL, board_arr[0][0].get_ownRect());
					board_arr[0][0].set_empty(false);
					board_arr[0][0].set_placedChar('X');
					return true;  // one place has been filled, and on one turn I can fill only one place
					break;
				}
				break;
			default:
				break;
			}
		}
		// if this  -  -  > combination does not work it is too early to return false we have to check other combinations as well 
	}
	
	/*    *
		  x

		  *
	*/

	if (board_arr[2][0].get_placedChar() == board_arr[0][0].get_placedChar())
	{
		if (board_arr[1][0].get_emptyness() == true)
		{
			switch (board_arr[0][0].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[1][0].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[1][0].get_ownTexture(), NULL, board_arr[1][0].get_ownRect());
					board_arr[1][0].set_empty(false);
					board_arr[1][0].set_placedChar('O');
					return true; // one place has been filled, and on one turn I can fill only one place 
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[1][0].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[1][0].get_ownTexture(), NULL, board_arr[1][0].get_ownRect());
					board_arr[1][0].set_empty(false);
					board_arr[1][0].set_placedChar('X');
					return true;  // one place has been filled, and on one turn I can fill only one place
					break;
				}
				break;
			default:
				break;
			}
		}
		// if this  -  -  > combination does not work it is too early to return false we have to check other combinations as well 
	}

	// if no combination works we have to let upper rowwise check know that from first row no place has been filled 
	// such that we go for second row

	return false;
}

bool Tic_Tac_Toe::second_column_check_block()
{
	/*    *
		  *
		  x
	*/

	
	if (board_arr[0][1].get_placedChar() == board_arr[1][1].get_placedChar())
	{
		if (board_arr[2][1].get_emptyness() == true)
		{
			switch (board_arr[1][1].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[2][1].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[2][1].get_ownTexture(), NULL, board_arr[2][1].get_ownRect());
					board_arr[2][1].set_empty(false);
					board_arr[2][1].set_placedChar('O');
					return true; // one place has been filled, and on one turn I can fill only one place 
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[2][1].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[2][1].get_ownTexture(), NULL, board_arr[2][1].get_ownRect());
					board_arr[2][1].set_empty(false);
					board_arr[2][1].set_placedChar('X');
					return true;  // one place has been filled, and on one turn I can fill only one place
					break;
				}
				break;
			default:
				break;
			}
		}
		// if this  -  -  > combination does not work it is too early to return false we have to check other combinations as well 
	}

	/*    x
		  *
		  *
	*/

	
	if (board_arr[2][1].get_placedChar() == board_arr[1][1].get_placedChar())
	{
		if (board_arr[0][1].get_emptyness() == true)
		{
			switch (board_arr[0][1].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[0][1].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][1].get_ownTexture(), NULL, board_arr[0][1].get_ownRect());
					board_arr[0][1].set_empty(false);
					board_arr[0][1].set_placedChar('O');
					return true; // one place has been filled, and on one turn I can fill only one place 
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[0][1].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][1].get_ownTexture(), NULL, board_arr[0][1].get_ownRect());
					board_arr[0][1].set_empty(false);
					board_arr[0][1].set_placedChar('X');
					return true;  // one place has been filled, and on one turn I can fill only one place
					break;
				}
				break;
			default:
				break;
			}
		}
		// if this  -  -  > combination does not work it is too early to return false we have to check other combinations as well 
	}

	/*    *
		  x

		  *
	*/

	if (board_arr[2][1].get_placedChar() == board_arr[0][1].get_placedChar())
	{
		if (board_arr[1][1].get_emptyness() == true)
		{
			switch (board_arr[1][1].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[1][1].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[1][1].get_ownTexture(), NULL, board_arr[1][1].get_ownRect());
					board_arr[1][1].set_empty(false);
					board_arr[1][1].set_placedChar('O');
					return true; // one place has been filled, and on one turn I can fill only one place 
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[1][1].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[1][1].get_ownTexture(), NULL, board_arr[1][1].get_ownRect());
					board_arr[1][1].set_empty(false);
					board_arr[1][1].set_placedChar('X');
					return true;  // one place has been filled, and on one turn I can fill only one place
					break;
				}
				break;
			default:
				break;
			}
		}
		// if this  -  -  > combination does not work it is too early to return false we have to check other combinations as well 
	}

	// if no combination works we have to let upper columnwise check know that from first row no place has been filled 
	// such that we go for second row

	return false;

}

bool Tic_Tac_Toe::third_column_check_block()
{
	/*    *
		  *
		  x
	*/


	if (board_arr[0][2].get_placedChar() == board_arr[1][2].get_placedChar())
	{
		if (board_arr[2][2].get_emptyness() == true)
		{
			switch (board_arr[1][2].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[2][2].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[2][2].get_ownTexture(), NULL, board_arr[2][2].get_ownRect());
					board_arr[2][2].set_empty(false);
					board_arr[2][2].set_placedChar('O');
					return true; // one place has been filled, and on one turn I can fill only one place 
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[2][2].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[2][2].get_ownTexture(), NULL, board_arr[2][2].get_ownRect());
					board_arr[2][2].set_empty(false);
					board_arr[2][2].set_placedChar('X');
					return true;  // one place has been filled, and on one turn I can fill only one place
					break;
				}
				break;
			default:
				break;
			}
		}
		// if this  -  -  > combination does not work it is too early to return false we have to check other combinations as well 
	}



	/*    x
		  *
		  *
	*/


	if (board_arr[2][2].get_placedChar() == board_arr[1][2].get_placedChar())
	{
		if (board_arr[0][2].get_emptyness() == true)
		{
			switch (board_arr[1][2].get_placedChar())
			{
			case 'X': // we should place exactly opposite
				if (our_single_user.get_symbol() != 'O')
				{
					board_arr[0][2].set_surface("assets/images/o.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][2].get_ownTexture(), NULL, board_arr[0][2].get_ownRect());
					board_arr[0][2].set_empty(false);
					board_arr[0][2].set_placedChar('O');
					return true; // one place has been filled, and on one turn I can fill only one place 
					break;
				}
				break;
			case 'O':
				if (our_single_user.get_symbol() != 'X')
				{
					board_arr[0][2].set_surface("assets/images/x.bmp", renderer);
					SDL_RenderCopy(renderer, board_arr[0][2].get_ownTexture(), NULL, board_arr[0][2].get_ownRect());
					board_arr[0][2].set_empty(false);
					board_arr[0][2].set_placedChar('X');
					return true;  // one place has been filled, and on one turn I can fill only one place
					break;
				}
				break;
			default:
				break;
			}
		}
		// if this  -  -  > combination does not work it is too early to return false we have to check other combinations as well 
	}

	// if no combination works we have to let upper columnwise check know that from first row no place has been filled 
	// such that we go for second row

	return false;
}