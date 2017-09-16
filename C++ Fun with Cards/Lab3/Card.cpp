#include "stdafx.h"
#include "Card.h"
using namespace std;


bool	//compares cards by rank, then suite
Card::operator< (const Card & card) const {
	return((int)rank < (int)card.rank) || (((int)rank == (int)card.rank) && ((int)suite < (int)card.suite));
};

bool	//checks equality of a card by making sure 2 cards have the same rank and suite
Card::operator== (const Card & card) const {
	return((int)rank == (int)card.rank && (int)suite == (int)card.suite);
};

int UsageMsg(char *name) {	//specifies program name, how to use program, and returns int 10
	cout << " Program Name: " << name << endl;
	cout << " To run this program, please input the name of a file in the form FileName.txt with valid card definitions separated by white space. " << endl;
	cout << "As an option, you can also input '-shuffle' to shuffle the deck of cards." << endl;
	return 10;
};
string ToStringSuites(Suites suite) {
	switch (suite) {
	case Suites::S:	return "S";
	case Suites::C: return "C";
	case Suites::H: return "H";
	case Suites::D: return "D";
	default: return "ERROR: Unknown Suite";
	}
};
string ToStringRanks(Ranks rank) {
	switch (rank) {
	case Ranks::two: return "2";
	case Ranks::three: return "3";
	case Ranks::four: return "4";
	case Ranks::five: return "5";
	case Ranks::six: return "6";
	case Ranks::seven: return "7";
	case Ranks::eight: return "8";
	case Ranks::nine: return "9";
	case Ranks::ten: return "10";
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
		C.rank = Ranks::two;
	}
	if (rank == '3') {
		C.rank = Ranks::three;
	}
	if (rank == '4') {
		C.rank = Ranks::four;
	}
	if (rank == '5') {
		C.rank = Ranks::five;
	}
	if (rank == '6') {
		C.rank = Ranks::six;
	}
	if (rank == '7') {
		C.rank = Ranks::seven;
	}
	if (rank == '8') {
		C.rank = Ranks::eight;
	}
	if (rank == '9') {
		C.rank = Ranks::nine;
	}
	if (rank == '1') {
		C.rank = Ranks::ten;
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
		C.suite = Suites::D;
	}
	if (suite == 'c' || suite == 'C') {
		C.suite = Suites::C;
	}
	if (suite == 'h' || suite == 'H') {
		C.suite = Suites::H;
	}
	if (suite == 's' || suite == 'S') {
		C.suite = Suites::S;
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
		if (b != std::end(allowSuites) && a2 != std::end(allowRanks3) && a1 != std::end(allowRanks3)) {
			return 1;
		}
	}
	return 20;
};
string PokerHandEval(vector<Card> &temp) {
	int ranker[15] = { 0 };
	int suiter[4] = { 0 };
	bool c5 = false, r4 = false, s4 = false, r3 = false, p1 = false, p2 = false, s5 = false;
	bool fullHouse = false;
	for (size_t j = 0; j < temp.size(); ++j) {	//sorts frequency of ranks
		Ranks r = temp[j].rank;
		int t = (int)r;
		++ranker[t];
	}
	for (size_t k = 0; k < temp.size(); k++) {	//sorts frequency of suites
		Suites s = (temp[k]).suite;
		int t = (int)s;
		++suiter[t];
	}
	for (int i = 2; i < size(ranker) - 4; i++) {
		if (ranker[i] == ranker[i + 1] && ranker[i + 1] == ranker[i + 2] && ranker[i + 2] == ranker[i + 3] && ranker[i + 3] == ranker[i + 4]) {
			if (ranker[i] == 1) {
				c5 = true;
			}
		}
	}
	for (int i = 0; i < size(ranker); ++i) {
		int count = ranker[i];

		if (count == 4) {
			r4 = true;	//four of a kind
			break;
		}

		if (count == 2) {

			if (p1) {
				p2 = true;
				continue;
			}
			if (!p1) {
				p1 = true;
				if (r3) {
					fullHouse = true;
					break;
				}
			}

		}

		if (count == 3) {
			r3 = true;
			if (p1) {
				fullHouse = true;
				break;
			}
		}

	}
	for (int i = 0; i < 4; i++) {
		int count = suiter[i];
		if (count == 5) {
			s5 = true;
			break;
		}
	}
	if (c5 && s5) {
		return "Straight Flush";
	}
	if (c5 && !s5) {
		return "Straight";
	}
	if (!c5 && s5) {
		return "Flush";
	}
	if (r4) {
		return "Four-of-a-Kind";
	}
	if (r3 && !fullHouse) {
		return "Three-of-a-Kind";
	}
	if (fullHouse) {
		return "Full House";
	}
	if (p1 && p2) {
		return "Two Pairs";
	}
	if (p1 && !p2) {
		return "One Pair";
	}
	else {
		return "No Rank";
	}

};
//int ErrorMsg(int e) {
//	if (e == 2) {
//		cout << "Error: File could not be opened. Please format input as filename.txt. " << endl;
//	}
//	if (e == 25) {
//		cout << "Error: No valid poker hands were found. Valid card definitions are 2 or 3 characters long, listed rank then suite. Each card definition should be separated by a space, tab, or other form of white space. " << endl;
//	}
//	if (e == 19) {
//		cout << "Error: You entered '-shuffle' with no input file. " << endl;
//	}
//	if (e == 23) {
//		cout << "Error: You've entered 2 command lines, but neither contain the input '-shuffle'." << endl;
//	}
//	if (e == 27) {
//		cout << "Error: You've entered more than 2 command lines" << endl;
//	}
//	if (e == 71) {
//		cout << "Error: The input file does not have enough cards (45) to deal 9 hands evenly." << endl;
//	}
//	return e;
//}





