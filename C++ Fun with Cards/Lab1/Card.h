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
	Queen=12,
	King=13,
	Ace=14,
};
struct Card {
	
//	Card(Ranks rank, Suites suite);
	Ranks rank;
	Suites suite;
//	int r_ = (int)rank;
//	int s_ = (int)suite;
	bool operator< (const Card &) const;
};


//define functions
int UsageMsg(char* name);
Card CreateCard(char rank, char suite);
int isValid(std::string word, int size);
string ToStringRanks(Ranks rank);
string ToStringSuites(Suites suite);
int CardPrinter(const std::vector<Card> &cards);
void HandCardPrinter(const vector<Card> &Deck);
int HandPrinter(const vector<Card> &Hands, const vector<string> &defs);
vector<string> PokerHand(const vector<Card> &Hands);
int Parse2(vector<Card> &Hand, char *p);
int Parser(std::vector<Card> &Deck, char *p);
string PokerHandEval(vector<Card> &temp);
void ErrorMsg(int e);

#endif /* CARD_H */#pragma once
