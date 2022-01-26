#pragma once
#ifndef _C_APP_H_
#define _C_APP_H_

#include <SDL.h>
#include <iostream>
#include <stdexcept>

using namespace std;

class CApp
{
private:
	bool game_running;
	const int WIDTH = 640;
	const int HEIGHT = 480;
	SDL_Window* window;
	SDL_Surface* surface;

public:
	CApp(): game_running{true}, window{nullptr}
	{	}
	int onExecute();
	bool onInit();
	void onEvent(SDL_Event* event);
	void onLoop();
	void onRender();
	void onCleanUp();
};


bool CApp::onInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	window = SDL_CreateWindow(
		"Our application | game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);

	if (window == NULL)
	{
		throw runtime_error("\n\nwindow could not be creted \n\n");
		return false;
	}

	return true;
}

void CApp::onEvent(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_QUIT:
		game_running = false;
		break;
	default:
		break;
	}
}

int CApp::onExecute()
{
	if (onInit() == false)
		return -1;
	SDL_Event event;

	while (game_running)
	{
		while (SDL_PollEvent(&event))
			onEvent(&event);
		//onLoop();
		//onRender();

	}

	onCleanUp();

	return 0;
}


void CApp::onCleanUp()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

#endif // !C_APP_H
