#ifndef PLAYER_H
#define PLAYER_H
#include "Hand.h"


struct Player {
	string Name;
	Hand hand;
	unsigned int handsWon;
	unsigned int handsLost;
	Player(const char *);
	void Load(const char *);
};

ostream& operator<<(ostream &, const Player &);
bool operator==(Player &, Player&);


#endif