#define ERRORS_H
#ifdef ERRORS_H
#include <iostream>
#include <string>
using namespace std;

enum class Errors {
	instance_not_available = 113,
	game_already_started = 117,
	invalid_index = 97,
	unknown_game = 137,
	no_game_in_progress = 151,
	already_playing = 179,
	no_players = 300,
	not_enough_cards_in_hand = 600,
};

int ErrorMsgs(int );

#endif 