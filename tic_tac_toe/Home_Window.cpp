

#include "Home_Window.h"

using namespace std;


Home_Window::Home_Window()
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

}


void Home_Window::Initiliase()
{
	welcome.set_dimensions(400, 20, 400, 50);

	rules.set_dimensions(140, 170, 100, 25);

	number_players.set_dimensions( 140, 205, 250, 27);
	single_player.set_dimensions(155, 242, 100, 15);
	multiple_player.set_dimensions(155, 267, 100, 15);
	for_single_player.set_dimensions(140, 242, 10, 10);
	for_single_player.set_active_state(true); // single player mode is on by default
	for_single_player.set_surface("assets/images/tick.bmp", renderer);
	for_multiple_player.set_dimensions(140, 267, 10, 10);
	for_multiple_player.set_surface("assets/images/tick.bmp", renderer);
	for_multiple_player.set_active_state(false); // multiple player mode is off by default

	level.set_dimensions(140, 240, 100, 25);

	list_rules.setALL(260, 100, 700, 550, "assets/images/rules.bmp", renderer);

	for_beginner_level.set_dimensions(140, 275, 10, 10);
	for_beginner_level.set_surface("assets/images/tick.bmp", renderer);
	for_beginner_level.set_active_state(true); // by default beginner level at the start of the game
	user_chosen_level = 1;
	for_basic_level.set_dimensions(140, 300, 10, 10);
	for_basic_level.set_surface("assets/images/tick.bmp", renderer);
	for_hard_level.set_dimensions(140, 325, 10, 10);
	for_hard_level.set_surface("assets/images/tick.bmp", renderer);

	rect_beginner_level.set_dimensions(155, 275, 50, 15);
	rect_basic_level.set_dimensions(155, 300, 40, 15);
	rect_hard_level.set_dimensions(155, 325, 40, 15);

	start.set_dimensions(700, 240, 100, 25);
}

void Home_Window::Execute(int& number_players, int& level)
{
	Initiliase();
	while (game_started == false)
	{
		Event_Handler(event);
		Render();
	}

	number_players = user_chosen_number_players;
	level = user_chosen_level;
}

void Home_Window::Event_Handler(SDL_Event& event)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			game_started = true;
		SDL_Point mousePosition;
		mousePosition.x = event.motion.x;
		mousePosition.y = event.motion.y;

		if (SDL_PointInRect(&mousePosition, start.get_ownRect()))
		{
			if(event.button.type == SDL_MOUSEBUTTONDOWN)
				game_started = true;
		}

		mouse_click_drop_down();
		user_input_number_players();
		user_input_game_level();
	}
}

void Home_Window::mouse_click_drop_down()
{
	SDL_Point mousePosition;
	mousePosition.x = event.motion.x;
	mousePosition.y = event.motion.y;

	drop_down_for_rules(mousePosition);
	drop_down_for_number_players(mousePosition);
	drop_down_for_level(mousePosition);
}

void Home_Window::drop_down_for_rules(SDL_Point& mousePosition)
{
	if (SDL_PointInRect(&mousePosition, rules.get_ownRect()))
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			if (rules.get_onclick() == false)
			{
				render_list_rules();
				rules.set_onclick(true);
				rules.set_shown(true);
			}
			else
			{
				SDL_RenderClear(renderer);
				rules.set_onclick(false);
				rules.set_shown(false);
			}
			
		}
	}
}

void Home_Window::drop_down_for_number_players(SDL_Point& mousePosition)
{
	if (SDL_PointInRect(&mousePosition, number_players.get_ownRect()))
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			if (number_players.get_onclick() == false)
			{
				put_tick();
				render_player_notes();
				number_players.set_onclick(true);
				number_players.set_shown(true);
			}
			else
			{
				SDL_RenderClear(renderer);
				number_players.set_onclick(false);
				number_players.set_shown(false);
			}
		}
	}
} 

void Home_Window::drop_down_for_level(SDL_Point& mousePosition)
{
	if (SDL_PointInRect(&mousePosition, level.get_ownRect()))
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{

			if (level.get_onclick() == false)
			{
				put_tick_for_levels();
				render_levels();
				level.set_onclick(true);
				level.set_shown(true);
			}
			else
			{
				SDL_RenderClear(renderer);
				level.set_onclick(false);
				level.set_shown(false);
			}

		}

	}
}

void Home_Window::Render()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	render_welcome();
	render_rules();
	if (rules.get_shown() == false)
	{
		render_number_players();
		if (number_players.get_shown() == false)
		{
			if (level.get_shown() == false)
			{
				render_level();
				render_start();
				
			}
			else
			{
				render_level();
				put_tick_for_levels();
				render_levels();
				render_start();
			}
		}
		else
		{
			SDL_RenderClear(renderer);
			render_welcome();
			render_rules();
			render_number_players();
			render_player_notes();
			put_tick();
			render_start();

		}
		
	}
	else
	{
		SDL_RenderClear(renderer);
		render_welcome();
		render_rules();
		render_list_rules();
	}
	
	SDL_RenderPresent(renderer);
}

void Home_Window::render_welcome()
{
	text_surface = TTF_RenderText_Solid(our_font, "Welcome to Tic Tac Toe Game!", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, welcome.get_ownRect());
}

void Home_Window::render_rules()
{
	text_surface = TTF_RenderText_Solid(our_font, "Rules", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, rules.get_ownRect());
}

void Home_Window::render_list_rules()
{
	SDL_RenderCopy(renderer, list_rules.get_ownTexture(), NULL, list_rules.get_ownRect());
}

void Home_Window::render_number_players()
{
	text_surface = TTF_RenderText_Solid(our_font, "Number of players", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, number_players.get_ownRect());
}

void Home_Window::render_level()
{
	text_surface = TTF_RenderText_Solid(our_font, "Level", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, level.get_ownRect());
}

void Home_Window::render_player_notes()
{
	text_surface = TTF_RenderText_Solid(our_font, "Single Player", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, single_player.get_ownRect());

	text_surface = TTF_RenderText_Solid(our_font, "Multiple Player", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, multiple_player.get_ownRect());
}

void Home_Window::render_single_player_rect()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, for_single_player.get_ownRect());
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Home_Window::render_multiple_player_rect()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, for_multiple_player.get_ownRect());
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Home_Window::render_start()
{
	text_surface = TTF_RenderText_Solid(our_font, "Start", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, start.get_ownRect());
}

void Home_Window::put_tick()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	if (for_single_player.get_active_state() == true)
	{
		SDL_RenderCopy(renderer, for_single_player.get_ownTexture(), NULL, for_single_player.get_ownRect());
	}
	else if(for_multiple_player.get_active_state() == true)
	{
		SDL_RenderDrawRect(renderer, for_single_player.get_ownRect());
		SDL_RenderCopy(renderer, for_multiple_player.get_ownTexture(), NULL, for_multiple_player.get_ownRect());
	}

	SDL_RenderDrawRect(renderer, for_multiple_player.get_ownRect());

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Home_Window::put_tick_for_levels()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	if (for_beginner_level.get_active_state() == true)
	{
		SDL_RenderCopy(renderer, for_beginner_level.get_ownTexture(), NULL, for_beginner_level.get_ownRect());
		SDL_RenderDrawRect(renderer, for_basic_level.get_ownRect());
		SDL_RenderDrawRect(renderer, for_hard_level.get_ownRect());
	}
	else
	{
		SDL_RenderDrawRect(renderer, for_beginner_level.get_ownRect());
		if (for_basic_level.get_active_state() == true)
		{
			SDL_RenderCopy(renderer, for_basic_level.get_ownTexture(), NULL, for_basic_level.get_ownRect());
			SDL_RenderDrawRect(renderer, for_hard_level.get_ownRect());
		}
		else
		{
			SDL_RenderDrawRect(renderer, for_basic_level.get_ownRect());
			if (for_hard_level.get_active_state() == true)
			{
				SDL_RenderCopy(renderer, for_hard_level.get_ownTexture(), NULL, for_hard_level.get_ownRect());
			}
			else
			{
				SDL_RenderDrawRect(renderer, for_hard_level.get_ownRect());
			}
		}
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	
}

void Home_Window::render_levels()
{
	put_tick_for_levels();
	text_surface = TTF_RenderText_Solid(our_font, "Beginner", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, rect_beginner_level.get_ownRect());
	
	text_surface = TTF_RenderText_Solid(our_font, "Basic", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, rect_basic_level.get_ownRect());
	
	text_surface = TTF_RenderText_Solid(our_font, "Hard", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, rect_hard_level.get_ownRect());

}

void Home_Window::user_input_number_players()
{
	SDL_Point mousePosition;
	mousePosition.x = event.motion.x;
	mousePosition.y = event.motion.y;

	if (SDL_PointInRect(&mousePosition, single_player.get_ownRect()) || SDL_PointInRect(&mousePosition, for_single_player.get_ownRect()))
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			user_chosen_number_players = 1; // single player mode is chosen
			for_single_player.set_active_state(true);
			for_multiple_player.set_active_state(false);
			cout << "\nnumber of players:  " << user_chosen_number_players << endl;
		}
	}
	else if (SDL_PointInRect(&mousePosition, multiple_player.get_ownRect()) || SDL_PointInRect(&mousePosition, for_multiple_player.get_ownRect()))
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			user_chosen_number_players = 2; // multiple player mode is chosen
			for_multiple_player.set_active_state(true);
			for_single_player.set_active_state(false);
			cout << "\nnumber of players:  " << user_chosen_number_players << endl;
		}
	}
}

void Home_Window::user_input_game_level()
{
	SDL_Point mousePosition;
	mousePosition.x = event.motion.x;
	mousePosition.y = event.motion.y;

	if (SDL_PointInRect(&mousePosition, rect_beginner_level.get_ownRect()) || SDL_PointInRect(&mousePosition, for_beginner_level.get_ownRect()))
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			user_chosen_level = 1;
			for_beginner_level.set_active_state(true);
			for_basic_level.set_active_state(false);
			for_hard_level.set_active_state(false);
			cout << "\ngame level :  " << user_chosen_level << endl;
		}

	}
	else if (SDL_PointInRect(&mousePosition, rect_basic_level.get_ownRect()) || SDL_PointInRect(&mousePosition, for_basic_level.get_ownRect()))
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			user_chosen_level = 2;
			for_beginner_level.set_active_state(false);
			for_basic_level.set_active_state(true);
			for_hard_level.set_active_state(false);
			cout << "\ngame level :  " << user_chosen_level << endl;
		}


	}
	else if (SDL_PointInRect(&mousePosition, rect_hard_level.get_ownRect()) || SDL_PointInRect(&mousePosition, for_hard_level.get_ownRect()))
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			user_chosen_level = 3;
			for_beginner_level.set_active_state(false);
			for_basic_level.set_active_state(false);
			for_hard_level.set_active_state(true);
			cout << "\ngame level :  " << user_chosen_level << endl;
		}


	}
}