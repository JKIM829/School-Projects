#include "stdafx.h"
#include "Deck.h"
#include <algorithm>
#include <random>

using namespace std;

ostream& operator<< (ostream& os, const Deck &deck) {	//basically, copy over the cardprinter method from lab0
	int t = deck.D.size();
	for (int s = 0; s < t; ++s) {
		Card temp = deck.D[s];
		Ranks temprank = temp.rank;
		Suites tempsuite = temp.suite;
		os << ToStringRanks(temprank) << ", " << ToStringSuites(tempsuite) << endl;
	}
	return os;
}//when you do a cout << Deck object, it will print card def per line from the Deck's card vector
void Deck::Load(char *p) {	//load method for a Deck
	ifstream ifs;
	ifs.open(p);

	if (!(ifs.is_open())) {
		cout << "Can't open file" << endl;
		throw 2;	//return 2 if no text file to open. Otherwise, you've opened it and you're ready to read.
	}
	if (ifs.is_open()) {
		string i;
		while (ifs >> i) {	//iterate through every word in the text file. This separates each word from the whitespaces
			if (i.size() == 2) {	//for each word that is 2 characters long, check to make sure there's a valid card def, then create card.
				if (isValid(i, 2) == 1) {
					Card C = CreateCard(i[0], i[1]);
					D.push_back(C);	//put the card into the card vector
				}
			}
			if (i.size() == 3) {		//for each word that is 3 characters long, check to make sure the input is rank/suite and create card.
				if (isValid(i, 3) == 1) {
					char input = '1';
					Card C = CreateCard(input, i[2]);
					D.push_back(C);	//put the card into the card vector.
				}
			}
		}

	}
	ifs.close();
};
Deck::Deck(char *p) {		//constructor calls on Load method
	try {
		Load(p);
	}
	catch (int r) {
		throw r;
	}
}
Deck::~Deck() {	//The compiler-supplied destructor is sufficient, since vectors have compiler supplied destructors
}
void Deck::shuffle() {	//shuffle method for D
	std::random_device rd;
	std::mt19937 rand(rd());
	std::shuffle(D.begin(), D.end(), rand);
	//random_shuffle(D.begin(), D.end()); DOES NOT WORK
}
const int Deck::size() {	//return number of elements in D
	return (const int)D.size();
}
Card Deck::pop() {			//returns and removes last card of Deck
	Card card = D.back();
	D.pop_back();
	return card;
}




