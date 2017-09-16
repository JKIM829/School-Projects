#include "stdafx.h"
#include "Hand.h"
using namespace std;


ostream& operator<< (ostream& os, const Hand &hand) {	//print out each card defintion in hand on a single line
	vector<Card> h = hand.H;
	for (size_t s = 0; s < hand.H.size(); ++s) {
		Card temp = hand.H[s];
		Ranks temprank = temp.rank;
		Suites tempsuite = temp.suite;
		os << ToStringRanks(temprank) << ToStringSuites(tempsuite) << " ";
	}
	os << endl;
	return os;
}
Hand& operator<< (Hand &hand, Deck &deck) {
	Card c = deck.pop();
	hand.push(c);
	sort(hand.H.begin(), hand.H.end());
	return hand;
}
Hand::Hand(const Hand& hand) {	//copy constructor
	H = hand.H;
}
HandRanks Hand::getHandRank() const {
	vector<Card> hands = H;
	string rank = PokerHandEval(hands);
	if (rank == "Straight Flush") {
		return HandRanks::straight_flush;
	}
	if (rank == "Straight") {
		return HandRanks::straight;
	}
	if (rank == "Flush") {
		return HandRanks::flush;
	}
	if (rank == "Four-of-a-Kind") {
		return HandRanks::four_kind;
	}
	if (rank == "Three-of-a-Kind") {
		return HandRanks::three_kind;
	}
	if (rank == "Full House") {
		return HandRanks::full_house;
	}
	if (rank == "Two Pairs") {
		return HandRanks::two_pairs;
	}
	if (rank == "One Pair") {
		return HandRanks::one_pair;
	}
	return HandRanks::no_rank;

}
Hand& Hand::operator= (const Hand &otherhand) {	//assignment operator
	if (&otherhand == this) {
		return *this;
	}
	else {
		H.clear();
		H = otherhand.H;
		return *this;
	}
}
int Hand::size() const {		//size operator
	return (const int)H.size();
};
bool Hand::operator== (const Hand &hand) const {	//equality operator
	if (H.size() != hand.H.size()) {
		return false;
	}
	else {
		for (size_t i = 0; i < H.size(); i++) {
			if (H[i] < hand.H[i] || hand.H[i] < H[i]) {
				return false;
			}
		}
	}
	return true;
}
bool Hand::operator< (const Hand &hand) const {
	if (H == hand.H) {	//first check: if same sequence, then false
		return false;
	}
	int t = H.size();
	for (int i = 0; i < t; ++i) {
		if (H[i] < hand.H[i]) {
			return true;
		}
		if (hand.H[i] < H[i]) {
			return false;
		}//only go to next card if the cards are equal.
	}
	return false;
}
string Hand::asString() const{
	string str = " ";
	Card temp;
	for (size_t i = 0; i != H.size(); ++i) {
		temp = H[i];
		Ranks temprank = temp.rank;
		Suites tempsuite = temp.suite;
		str += ToStringRanks(temp.rank);
		str += ToStringSuites(temp.suite);
		str += " ";
	}
	return str;
};
void Hand::push(Card c) { //adds a card to the hand, sorts it
	H.push_back(c);
	std::sort(H.begin(), H.end());
}
vector<Card> Hand::getCards() const {
	return H;
}
string HandRanks_toString(const HandRanks &hr) {
	switch (hr) {
	case HandRanks::no_rank:
		return "No Rank";
	case HandRanks::one_pair:
		return "One Pair";
	case HandRanks::two_pairs:
		return "Two Pairs";
	case HandRanks::three_kind:
		return "Three of a Kind";
	case HandRanks::four_kind:
		return "Four of a Kind";
	case HandRanks::straight:
		return "Straight";
	case HandRanks::straight_flush:
		return "Straight Flush";
	case HandRanks::flush:
		return "Flush";
	case HandRanks::full_house:
		return "Full House";
	}
	return "Cannot Identify";
}