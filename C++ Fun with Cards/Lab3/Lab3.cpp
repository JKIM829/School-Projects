// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FiveCardDraw.h"

int UserMsg(char *);


int main(int argc, char* argv[])
{
	if (argc < 4) {
		return UserMsg(argv[0]);
	}

	shared_ptr<Game> thegame; 

	try {
		Game::start_game(argv[1]);
		shared_ptr<Game> thisgame = Game::instance();
		thegame = thisgame;

		//add players
		for (int i = 2; i < argc; ++i) {
			thisgame->add_player(argv[i]);
		}

		cout <<endl << "The game " << argv[1] << " has started. Current players: " << endl;
		for (int i = 2; i < argc; ++i) {
			cout  <<argv[i] << endl;
		}
		cout << endl;

		while(thisgame->num_players() > 1){
			cout << endl<< "***** BEFORE ROUND *****" << endl;
			cout << endl;
			thisgame->before_round();
			cout << endl;
			cout << "***** ROUND *****" << endl << endl;
			thisgame->round();
			cout << "***** AFTER ROUND *****" << endl << endl;
			thisgame->after_round();
		}

		if (thisgame->num_players() <= 1) {
			thisgame->stop_game();
			cout << "Not enough players. Game over!" << endl;

			return 0;
		}
	}
	catch (int r) {
		thegame->stop_game();
		return ErrorMsgs(r);
	}
	//in case I can't catch something, then I'll at least be able to trace back to this
	catch (...) {
		return 5000;
	}
    return 0;
}

//Just small helper method for main
int UserMsg(char *p) {
	cout << "Program: " << p << endl;
	cout << "Please enter the name of the game and the names of 2 or more players, separated by spaces." << endl;
	return 75;
}


