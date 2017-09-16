#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <iterator>
#include <algorithm>
using namespace std;

enum class Suites {
	C = 0, D = 1, H = 2, S = 3
};
enum class Ranks {
	two = 2,
	three = 3,
	four = 4,
	five = 5,
	six = 6,
	seven = 7,
	eight = 8,
	nine = 9,
	ten = 10,
	Jack = 11,
	Queen = 12,
	King = 13,
	Ace = 14,
};
struct Card {
	Ranks rank;
	Suites suite;
	bool operator< (const Card &) const;
	bool operator== (const Card &) const;
};


//define functions
int UsageMsg(char* name);
string ToStringRanks(Ranks rank);
string ToStringSuites(Suites suite);
Card CreateCard(char rank, char suite);
int isValid(std::string word, int size);
string PokerHandEval(vector<Card> &temp);
int ErrorMsg(int e);


#endif /* CARD_H */
