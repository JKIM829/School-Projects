#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include <memory>

using namespace std;

class Game  {
protected: 
	static shared_ptr<Game> game_pointer;
	Deck mainDeck = Deck();
	vector<shared_ptr<Player>> players;
public: 
	static shared_ptr<Game> instance();
	static void start_game(const string&);
	static void stop_game();
	void add_player(const string&);
	shared_ptr<Player> find_player(const string&);
	int num_players() {
		return players.size();
	}
	virtual ~Game() {};

	virtual int before_turn(Player &) = 0;

	virtual int turn(Player &) = 0;

	virtual int after_turn(Player &) = 0;

	virtual int before_round() = 0;

	virtual int round() = 0;

	virtual int after_round() = 0;

};


#endif