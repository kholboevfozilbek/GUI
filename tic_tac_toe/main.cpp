

#include "Tic_Tac_Toe.h"
#include "Home_Window.h"

int main(int argc, char* args[])
{
	Tic_Tac_Toe game;
	Home_Window h;

	int number_players;
	int level;

	h.Execute(number_players, level);

	h.Free_Resources();
	cout << "\nNumber of players:  " << number_players << endl;
	cout << "\nLevel:  " <<  level << endl;

	game.set_player_level(number_players, level);

	game.Execute();
	return 0;
}