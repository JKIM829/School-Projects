#include "Card.h"

using namespace std;



int UsageMsg() {	//specifies program name, how to use program, and returns int 10
	cout << " Program Name: Lab0" << endl;
	cout << " To run this program, please input the name of a file in the form FileName.txt with valid card definitions. " << endl;
	return 10;
};
string ToStringSuites(Suites suite) {
	switch (suite) {
	case Suites::S:	return "Spades";
	case Suites::C: return "Clubs";
	case Suites::H: return "Hearts";
	case Suites::D: return "Diamonds";
	default: return "ERROR: Unknown Suite";
	}
};

string ToStringRanks(Ranks rank) {
	switch (rank) {
	case Ranks(2): return "2";
	case Ranks(3): return "3";
	case Ranks(4): return "4";
	case Ranks(5): return "5";
	case Ranks(6): return "6";
	case Ranks(7): return "7";
	case Ranks(8): return "8";
	case Ranks(9): return "9";
	case Ranks(10): return "10";
	case Ranks::Jack: return "J";
	case Ranks::Queen: return "Q";
	case Ranks::King: return "K";
	case Ranks::Ace: return "A";
	default: return "ERROR: Unknown Rank";
	}
};

Card CreateCard(char rank, char suite) {	//function that creates a card given a valid card def string
	Card C;
	if (rank == '2') {
		C.rank = Ranks(2);
	}
	if (rank == '3') {
		C.rank = Ranks(3);
	}
	if (rank == '4') {
		C.rank = Ranks(4);
	}
	if (rank == '5') {
		C.rank = Ranks(5);
	}
	if (rank == '6') {
		C.rank = Ranks(6);
	}
	if (rank == '7') {
		C.rank = Ranks(7);
	}
	if (rank == '8') {
		C.rank = Ranks(8);
	}
	if (rank == '9') {
		C.rank = Ranks(9);
	}
	if (rank == '1') {
		C.rank = Ranks(10);
	}
	if (rank == 'j' || rank == 'J') {
		C.rank = Ranks::Jack;
	}
	if (rank == 'q' || rank == 'Q') {
		C.rank = Ranks::Queen;
	}
	if (rank == 'k' || rank == 'K') {
		C.rank = Ranks::King;
	}
	if (rank == 'A' || rank == 'a') {
		C.rank = Ranks::Ace;
	}
	if (suite == 'd' || suite == 'D') {
		C.suite = Suites(1);
	}
	if (suite == 'c' || suite == 'C') {
		C.suite = Suites(0);
	}
	if (suite == 'h' || suite == 'H') {
		C.suite = Suites(2);
	}
	if (suite == 's' || suite == 'S') {
		C.suite = Suites(3);
	}

	return C;
};

int isValid(string word, int size) {	//returns 1 if the word is a valid card definition, checks input has valid card def characters 
	char allowRanks[18] = { '2','3','4','5','6','7','8','9','j','J','q','Q','k','K','a','A','d','D' };
	char allowSuites[8] = { 'd','D','s','S','h','H','c','C' };
	char allowRanks3[20] = { '0', '1', '2','3','4','5','6','7','8','9','j','J','q','Q','k','K','a','A','d','D' };
	
	if (size == 2) {
		char *a = std::find(std::begin(allowRanks), std::end(allowRanks), word[0]);	//searches through allowable array to see if the word is valid
		char *b = std::find(std::begin(allowSuites), std::end(allowSuites), word[1]);
		// When the element is not found,a or be are at the end of allowable chars.
		if (a != std::end(allowRanks) && b != std::end(allowSuites)) {
			return 1;
		}
	}

	if (size == 3 && word[0] == '1' && word[1] == '0') {
		char *b = std::find(std::begin(allowSuites), std::end(allowSuites), word[2]);
		// If last character is not a suite, then you return 20 == not valid card def
		char *a1 = std::find(std::begin(allowRanks3), std::end(allowRanks3), word[0]);
		char *a2 = std::find(std::begin(allowRanks3), std::end(allowRanks3), word[1]);
		if (b!= std::end(allowSuites) && a2 != std::end(allowRanks3) && a1 != std::end(allowRanks3)) {
			return 1;
		}
	}
	return 20;
};

int CardPrinter(const vector<Card> &Deck) {
	//Prints out valid card definitions from supplied vector
	for (size_t s = 0; s < Deck.size(); ++s) {
		Card temp = Deck[s];
		Ranks temprank = temp.rank;
		Suites tempsuite = temp.suite;
		cout << ToStringRanks(temprank) << ", " << ToStringSuites(tempsuite) << endl;
	}
	return 0;
};

int Parser(vector<Card> &Deck, char *p) {
	ifstream ifs;
	ifs.open(p);
	
	if (!(ifs.is_open())) {
		throw 2;	//return 2 if no text file to open. Otherwise, you've opened it and you're ready to read.
		return 2;
	}
	if (ifs.is_open()) {
		string i;
		Card C;
		while (ifs >> i) {	//iterate through every word in the text file. This separates each word from the whitespaces
			if (i.size() == 2) {	//for each word that is 2 characters long, check to make sure there's a valid card def, then create card.
				if (isValid(i,2) == 1) {
					C = CreateCard(i[0], i[1]);
					Deck.push_back(C);	//put the card into the card vector
				}
			}
			if (i.size() == 3) {		//for each word that is 3 characters long, check to make sure the input is rank/suite and create card.
				if (isValid(i,3) == 1) {
					char input = '1';
					C = CreateCard(input, i[2]);
					Deck.push_back(C);	//put the card into the card vector.
				}
			}
		}

		const vector<Card> cards = Deck;

		if (cards.empty()) {
			int i = 25;	//return 25 if no valid card definitions in the text file.
			throw i;
		}
	}
	ifs.close();
	return 0;
};

void ErrorMsg(int e) {	//in the try/catch block, there are only 2 possible catches resulting from error.
	if (e == 2) {
		cout << "Error: File could not be opened. Please format input as filename.txt. " << endl;
	}
	if (e == 25) {
		cout << "Error: No valid card defintions were found. Valid card definitions are 2 or 3 characters long, listed rank then suite. Each card definition should be separated by a space, tab, or other form of white space." << endl;
	}
}





