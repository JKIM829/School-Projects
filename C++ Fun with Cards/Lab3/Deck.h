#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <ostream>
using namespace std;


class Deck {
	friend class Hand; //lets the << operator work later
	friend ostream& operator<< (ostream &, const Deck &);

private:
	vector<Card> D;

public:
	//void Load(char *);
	Deck(); //Constructor: takes a file name, passes it to load method
	virtual ~Deck();	//Destructor
	void shuffle();
	const int size();
	void add_card(Card);
	Card pop();	//this returns and removes back of deck
	void resetDeck();
};


#endif /*DECK_H*/
