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

enum  Suites { C=0, D=1, H=2, S=3 };

enum  Ranks {
	Two = 2,
	two = 2,
	Three = 3,
	three = 3,
	Four = 4,
	four = 4,
	Five = 5,
	five = 5,
	Six = 6,
	six = 6,
	Seven = 7,
	seven = 7,
	Eight = 8,
	eight = 8,
	Nine = 9,
	nine = 9,
	Ten = 10,
	ten = 10,
	Jack,
	Queen,
	King,
	Ace,
};

typedef struct Card {
	Ranks rank;
	Suites suite;
};
Card;

//define functions
int UsageMsg();
Card CreateCard(char rank, char suite);
int isValid(std::string word, int size);
int CardPrinter(const std::vector<Card> &cards);
int Parser(std::vector<Card> &Deck, char *p);
void ErrorMsg(int e);
#endif /* CARD_H */