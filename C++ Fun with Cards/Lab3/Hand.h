#ifndef HAND_H
#define HAND_H
#include "Deck.h"
#include "Card.h"
using namespace std;

enum class HandRanks {
	no_rank,
	one_pair,
	two_pairs,
	three_kind,
	straight,
	flush,
	full_house,
	four_kind,
	straight_flush
};

class Hand {
	friend ostream& operator<< (ostream &, const Hand &);
	friend Hand& operator<< (Hand &, Deck &);

private:
	vector<Card> H;
	HandRanks h_rank;

public:
	Hand() {};	//sufficient, since each initialized hand object will have a vector<Card> that's initially empty 
	Hand(const Hand&);
	~Hand() {};	//destructor, sufficient because vectors have compiler supplied destructor
	void setHandRank() ;
	HandRanks getHandRank() const;
	Hand& operator= (const Hand &);
	int size() const;
	bool operator== (const Hand &) const;
	bool operator< (const Hand &) const;
	Card operator[] (size_t);
	void remove_card(size_t);
	string asString() const;
	void push(Card c);
	vector<Card> getCards() const;
	void clearHand();
	void sortHand();
};

//Declare functions here:

string HandRanks_toString(const HandRanks &);


#endif /*HAND_H*/