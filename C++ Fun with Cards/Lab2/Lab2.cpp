// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Hand.h"
using namespace std;

void dealer(Deck &d, vector<Hand> &h);
void HandPrinter(vector<Hand> &thisHand);
int pairHelper(vector<Card> &cards);
bool poker_rank(const Hand &h, const Hand &h2);


int main(int argc, char* argv[])
{
		//no arguments
		if (argc == 1) {
			int r = UsageMsg(argv[0]);
			return r;
		}
		//1 argument
		if (argc == 2 && strcmp(argv[1], "-shuffle")==0) {
				return ErrorMsg(19);
			}
			
		//2 arguments
		if (argc == 3 && strcmp(argv[1],"-shuffle") !=0 && strcmp(argv[2], "-shuffle") != 0) {
			return ErrorMsg(23);
		}
		if (argc > 3) {
			return ErrorMsg(27);
		}
		else {
			char * file = argv[1];
			if (argc == 3 && strcmp(argv[1], "-shuffle") == 0) {
				file = argv[2];
			}

			try{
				Deck thisDeck(file);

				if (argc == 3) {
					thisDeck.shuffle();
					cout << "The deck is shuffled." << endl;
				}

				if (thisDeck.size() < 45) {
					cout << "Not enough card defintions in " << file << endl;
					return 71;
				}

				std::vector<Hand> hands;
				
				for (int i = 0; i < 9; ++i) {
					Hand newHand;
					hands.push_back(newHand);
				}

				dealer(thisDeck, hands);	//deals the deck into 9 hands

				cout << "This is the deck after dealing 9 hands: " << endl;
				cout << thisDeck << endl;
				cout << endl;
				cout << "These are the hands before sorting: " << endl;
				HandPrinter(hands);
				cout << endl;
				cout << "These are the hands after sorting: " << endl;
				std::sort(hands.begin(), hands.end());	//sort the hands using STL sort algorithm
				HandPrinter(hands);
				cout << endl;
				cout << "These are the hands after sorting by poker rank: " << endl;
				std::sort(hands.begin(), hands.end(), poker_rank);
				HandPrinter(hands);
				cout << "Done" << endl;
				return 0;
			}
			catch (int r) {
				return ErrorMsg(r);
			}
		}
	
};

void dealer(Deck &d, vector<Hand> &h) {
	int i = 0;
	while (i < 5) {
		for (int c = 0; c < 9; ++c) {
			h[c] << (h[c],d);
		}
		++i;
	}
};

void HandPrinter(vector<Hand> &thisHand) {
	for (size_t i = 0; i < thisHand.size(); ++i) {
		HandRanks r = thisHand[i].getHandRank();
		cout << HandRanks_toString(r) << " ";
		cout << thisHand[i].asString() << endl;
	}
};

int pairHelper(vector<Card> &cards) {	//returns the index of the first card in a pair
	for (size_t i = 0; i < (cards.size() - 1); ++i) {
		if (cards[i].rank == cards[i + 1].rank) {
			return i;
		}
	}
	return 0;
};

bool poker_rank(const Hand &h, const Hand &h2) {
	HandRanks r1 = h.getHandRank();
	HandRanks r2 = h2.getHandRank();
	int Rank1 = (int)r1;
	int Rank2 = (int)r2;

	if (Rank1 != Rank2) {
		return Rank1 < Rank2;
	}
	if (Rank1 == Rank2) {
		vector<Card> v1 = h.getCards();
		vector<Card> v2 = h2.getCards();
		
		switch (r1) {
		case HandRanks::straight_flush: {
			return (v1[4].operator<(v2[4])); }

		case HandRanks::four_kind: {
			return (v1[2].rank < v2[2].rank); }	// rank of 4-kind should found in the middle

		case HandRanks::full_house: {
			if (v1[2].rank == v2[2].rank) {	//if the ranks of the 3cards are the same, 4 cases where 2pair's index is:
				if (v1[2].rank == v1[3].rank && v2[2].rank == v2[3].rank) {
					return v1[0].rank < v2[0].rank;
				}
				if (v1[2].rank == v1[3].rank && v2[2].rank == v2[1].rank) {
					return v1[0].rank < v2[4].rank;
				}
				if (v1[2].rank == v1[1].rank && v2[2].rank == v2[3].rank) {
					return v1[4].rank < v2[0].rank;
				}
				return v1[4].rank < v2[4].rank;
			}
			return v1[2].rank < v2[2].rank; }

		case HandRanks::flush: {
			for (size_t i = v1.size()-1; i > 0; --i) {
				if (v1[i].rank == v2[i].rank) {
					continue;
				}
				else {
					return v1[i].rank < v2[i].rank;
				}
			}
			return v1[0].rank < v2[0].rank; }

		case HandRanks::straight: {
			return v1[4].operator<(v2[4]); }	//highest cards are at last position

		case HandRanks::three_kind: {
			return v1[2].rank < v2[2].rank; }

		case HandRanks::two_pairs: {
			if (v1[3].rank == v2[3].rank) {	//highest pairs are equal
				if (v1[1].rank == v2[1].rank) {//2nd pairs are equal, sort by 5th card
					//6 cases where the 5th card in each hand is
					if (v1[0].rank == v1[1].rank && v1[2].rank == v1[3].rank ) {	//5th card in last position for v1
						if (v2[0].rank == v2[1].rank && v2[2].rank == v2[3].rank) {	//5th card is in last for v2
							return v1[4].rank < v2[4].rank;
						}
						if (v2[0].rank == v2[1].rank && v2[3].rank == v2[4].rank) {	//5th card is in middle for v2
							return v1[4].rank < v2[2].rank;
						}
						if (v2[1].rank == v2[2].rank && v2[3].rank == v2[4].rank) {	//5th card is in beginning for v2
							return v1[4].rank < v2[0].rank;
						}
					}

					if (v1[0].rank == v1[1].rank && v1[3].rank == v1[4].rank) {	//5th card is in middle position for v1
						if (v2[0].rank == v2[1].rank && v2[2].rank == v2[3].rank) {	//5th card is in last for v2
							return v1[2].rank < v2[4].rank;
						}
						if (v2[0].rank == v2[1].rank && v2[3].rank == v2[4].rank) {	//5th card is in middle for v2
							return v1[2].rank < v2[2].rank;
						}
						if (v2[1].rank == v2[2].rank && v2[3].rank == v2[4].rank) {	//5th card is in beginning for v2
							return v1[2].rank < v2[0].rank;
						}
					}
					if (v1[1].rank == v1[2].rank && v1[3].rank == v1[4].rank) {	//5th card is in first position for v1
						if (v2[0].rank == v2[1].rank && v2[2].rank == v2[3].rank) {	//5th card is in last for v2
							return v1[0].rank < v2[4].rank;
						}
						if (v2[0].rank == v2[1].rank && v2[3].rank == v2[4].rank) {	//5th card is in middle for v2
							return v1[0].rank < v2[2].rank;
						}
						if (v2[1].rank == v2[2].rank && v2[3].rank == v2[4].rank) {	//5th card is in beginning for v2
							return v1[0].rank < v2[0].rank;
						}
					}
				}
				return v1[1].rank < v2[1].rank;	//return by rank of 2nd pair
			}
			return v1[3].rank < v2[3].rank; }	//return by rank of 1st pair

		case HandRanks::one_pair: {
			int p1 = pairHelper(v1);	//index of the first card in the pair in first hand
			int p2 = pairHelper(v2);	//index of the first card in the pair in second hand
			if (v1[p1].rank != v2[p2].rank) {
				return v1[p1].rank < v2[p2].rank;
			}
			if (v1[p1].rank == v2[p2].rank) {	//if the pairs have the same rank
				v1.erase(v1.begin() + p1, v1.begin() + (p1 + 1));	//remove the pair from v1
				v2.erase(v2.begin() + p2, v2.begin() + (p2 + 1));	//remove the pair from v2
				for (size_t i = v1.size() - 1; i > 0; --i) {
					if (v1[i] == v2[i]) {
						continue;
					}
					return v1[i].operator<(v2[i]);
				}
			}
			return v1[0].rank < v2[0].rank;
		}

		case HandRanks::no_rank: {
			for (size_t i = v1.size() - 1; i != 0; i--) {
				if (v1[i].rank != v2[i].rank) {
					return v1[i].rank < v2[i].rank;
				}
			}
			return v1[0].rank < v2[0].rank; }
			
		default: return Rank1 < Rank2;
		}
	}
	return false;
}