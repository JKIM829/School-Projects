#include "stdafx.h"
#include "Game.h"
#include "FiveCardDraw.h"

shared_ptr<Game> Game::game_pointer = 0;

shared_ptr<Game> Game::instance() {
	if (game_pointer == 0) {
		throw 113;
	}
	else {
		return game_pointer;
	}
};

void Game::start_game(const string& s) {
	if (game_pointer != 0) {
		throw 117;
	}
	else {
		if (s.find("FiveCardDraw") != std::string::npos) {	//if "FiveCardDraw" is found in the supplied string, 
			game_pointer = make_shared<FiveCardDraw> (FiveCardDraw());
			//make shared to instance of fivecarddraw class and store its address in the static pointer member variable.
		 }
		else {
			throw 137;
		}
	}
}

void Game::stop_game() {
	if (game_pointer.unique()) {
		throw 151;
	}
}

void Game::add_player(const string &s) {
	for (size_t i = 0; i < players.size(); ++i) {
		Player p = *players[i];
		if (p.Name.compare(s) == 0) {
			throw 179;
		}
	}
	shared_ptr<Player> p = make_shared<Player>(Player(s.c_str()));
	players.push_back(p);
}

shared_ptr<Player> Game::find_player(const string&s) {
	for (size_t i = 0; i < players.size(); ++i) {
		Player p = *players[i];
		if ((p.Name).compare(s)==0) {	//if you find a matching name
			return players[i];			//return the shared_ptr of the player
		}
	}
	return 0;	//else, return a singulare shared ptr
}

