#include "stdafx.h"
#include "Player.h"

Player::Player(const char *p) {
	Name = p;
	handsLost = 0;
	handsWon = 0;
	Load(p);
}

void Player::Load(const char *p) {	//load method for a Player
	int count = 0;
	ifstream ifs;
	bool wread = false;
	bool lread = false;
	ifs.open(p);

	if (!(ifs.is_open())) {
		return;
	}
	if (ifs.is_open()) {
		string i;
		while (ifs >> i) {	//iterate through every word in the text file. This separates each word from the whitespaces
			if (count == 0) {
				Name = i;
				++count;
				continue;
			}
			if (count == 1) {
				int won = stoi(i);
				handsWon = won;
				wread = true;
				++count;
				continue;
			}
			if (count == 2) {
				int lost = stoi(i);
				handsLost = lost;
				lread = true;
				++count;
				continue;
			}
			if (!(lread&&wread)) {	//if either HandsWon or HandsLost couldn't be read from the file, set both to 0.
				handsLost = 0;
				handsWon = 0;
				continue;
			}
			if (count > 2) {
				break;
			}
		}
	}
	ifs.close();
};

ostream& operator<<(ostream & os, const Player &p) {
	os <<"Player: " << p.Name << " Hands won: " << p.handsWon << " Hands lost: " << p.handsLost << " Hand: " << p.hand << endl;
	return os;
};

bool operator==(Player &p1, Player &p2)  {
	return(p1.Name.compare(p2.Name) == 0);
}
