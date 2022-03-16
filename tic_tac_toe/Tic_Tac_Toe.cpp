
#include "Tic_Tac_Toe.h"
#include <string>
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

void Tic_Tac_Toe::Execute()
{
	Initialise();

	while (game_started == false)
	{
		handle_main_window_event();
		render_main_window();
		Render();

	}

	while (running)
	{
		Event_Handler(event);
		Render();
	}
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

	generate_home_window();
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


	SDL_RenderPresent(renderer);
}

void Tic_Tac_Toe::generate_the_board()
{

}

void Tic_Tac_Toe::generate_home_window()
{
	welcome.x = 400;
	welcome.y = 20;
	welcome.w = 400;
	welcome.h = 50;

	rules.x = 140;
	rules.y = 170;
	rules.w = 100;
	rules.h = 25;

	number_players.x = 140;
	number_players.y = 205;
	number_players.w = 250;
	number_players.h = 27;

	level.x = 140;
	level.y = 240;
	level.w = 100;
	level.h = 25;

	list_rules.x = 260;
	list_rules.y = 205;
	list_rules.w = 700;
	list_rules.h = 400;

}

void Tic_Tac_Toe::handle_main_window_event()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			running = false;

		mouse_press_for_drop_down(event);
	}
}

void Tic_Tac_Toe::mouse_press_for_drop_down(SDL_Event& event)
{
	SDL_Point mousePosition;

	mousePosition.x = event.motion.x;
	mousePosition.y = event.motion.y;	

	mouse_press_for_rules(mousePosition);
}

void Tic_Tac_Toe::mouse_press_for_rules(SDL_Point mousePosition)
{
	if (SDL_PointInRect(&mousePosition, &rules))
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			if (on_click == false)
			{
				SDL_RenderDrawRect(renderer, &list_rules);
			}
		}
	}
}

void Tic_Tac_Toe::render_main_window()
{
	text_surface = TTF_RenderText_Solid(our_font, "Welcome to Tic Tac Toe Game!", {0, 255, 0});
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, &welcome); 

	text_surface = TTF_RenderText_Solid(our_font, "Rules", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, &rules);

	text_surface = TTF_RenderText_Solid(our_font, "Number of players", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, &number_players);

	text_surface = TTF_RenderText_Solid(our_font, "Level", { 0, 255, 0 });
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_RenderCopy(renderer, text_texture, NULL, &level);

}