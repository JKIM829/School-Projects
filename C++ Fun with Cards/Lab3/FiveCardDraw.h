#define FIVECARDDRAW_H
#ifdef FIVECARDDRAW_H

#include "Game.h"

class FiveCardDraw: public Game {

protected:
	size_t dealer;
	Deck discard_deck;
	//helper methods for after_round()
	void resetDeck();
	bool WannaLeave();
	bool WannaJoin();
	void makePlayerFile(shared_ptr<Player>);
	void finalPlayer(shared_ptr<Player>&);

public:
	FiveCardDraw();
	virtual int before_turn(Player &);
	virtual int turn(Player &);
	virtual int after_turn(Player&);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};

#endif