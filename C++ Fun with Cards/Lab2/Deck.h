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
	void Load(char *);
	Deck(char *); //Constructor: takes a file name, passes it to load method
	virtual ~Deck();	//Destructor
	void shuffle();
	const int size();
	Card pop();	//this returns and removes back of deck
};


#endif /*DECK_H*/
