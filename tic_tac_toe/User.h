

#pragma once


#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>


using namespace std;

class User
{
private:
	char user_symbol='\0';
	bool user_turn;

public:
	User()
	{

	}
	User(char symbol, bool turn) {
		user_symbol = symbol;
		user_turn = turn;
	}

	void setALL(char symbol, bool turn) {
		user_symbol = symbol;
		user_turn = turn;
	}

	void set_symbol(char ch)
	{
		user_symbol = ch;
	}

	void set_turn(bool state) {
		user_turn = state;
	}

	char get_symbol() { return user_symbol;  }
	bool get_turn() { return user_turn;  }
};