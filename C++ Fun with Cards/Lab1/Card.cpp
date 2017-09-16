#include "stdafx.h"
#include "Card.h"
using namespace std;



int UsageMsg(char *name) {	//specifies program name, how to use program, and returns int 10
	cout << " Program Name: " << name  << endl;
	cout << " To run this program, please input the name of a file in the form FileName.txt with valid card definitions, 5 per line. " << endl;
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


bool	//compares cards by rank, then suite
Card::operator< (const Card & card) const {
	return((int)rank < (int)card.rank) || (((int)rank == (int)card.rank) && ((int)suite < (int)card.suite));
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

void HandCardPrinter(const vector<Card> &Deck) {
	//Prints out valid card definitions from supplied vector, for card hands
	for (size_t s = 0; s < Deck.size(); ++s) {
		Card temp = Deck[s];
		Ranks temprank = temp.rank;
		Suites tempsuite = temp.suite;
		cout << ToStringRanks(temprank) << ToStringSuites(tempsuite) << " " ;
	}
	cout << ":";
};	//right after this, print out the poker hand of the cards using the PokerHandEval supplied vector of strings


string PokerHandEval(vector<Card> &temp) {
	int ranker[15] = { 0 };
	int suiter[4] = {0};

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
	if (p1&&!p2) {
		return "One Pair";
	}
	else {
		return "No Rank";
	}

};

vector<string> PokerHand(const vector<Card> &Hands) {	//feed sorted hand of cards to this function
	int i = 0;
	vector<Card> temp;
	vector<string> PHands;
		for (i; i < Hands.size(); i++) {
			temp.push_back(Hands[i]);

				if (i % 5 == 4) {	//make sure to load temp vector with only 5 cards
					PHands.push_back(PokerHandEval(temp));	//evaluate hand, push string onto string vector
					temp.clear();	//clear hand
					continue;		//get out of this iteration, go to next hand with i = some mult of 5.
				}
		}
	return PHands;
};

int HandPrinter(const vector<Card> &Hands, const vector<string> &defs) {
	vector<Card> temp;
	int j = 0;
	int i = 0;
	while (j < defs.size()) {
		for (i; i < Hands.size(); i++) {
			temp.push_back(Hands[i]);
			if (i % 5 == 4) {	//make sure to load temp vector with only 5 cards
				HandCardPrinter(temp);	//print out the cards on one line
				cout << defs[j] << endl;	//print out the poker hand of the cards right after
				++j;
				temp.clear();	//clear hand
				continue;		//get out of this iteration, go to next hand with i = some mult of 5.
			}
		}
	}
	return 1;
};

int Parse2(vector<Card> &Hand, char *p) {	//Parsing function for Lab1
	ifstream ifs;
	ifs.open(p);
	vector<Card> temp;
	if (!(ifs.is_open())) {
		throw 2;	//return 2 if no text file to open. Otherwise, you've opened it and you're ready to read.
		return 2;
	}
	if (ifs.is_open()) {
		string line1;
		string line;
		string i;
		stringstream iss;
		while (getline(ifs, line1)) {	//get the entire line, store in string stream
			iss << line1;
			while (getline(iss, line, '/')) {	//then, read through the line until you reach the / or the end.
				stringstream word(line);
				while (word >> i) {	//read the line word by word, separated by white spaces
					if (i.size() == 2) {	//for each word that is 2 characters long, check to make sure there's a valid card def, then create card.
						if (isValid(i, 2) == 1) {
							Card C = CreateCard(i[0], i[1]);
							temp.push_back(C);	//put the card into the card vector
						}
					}
					if (i.size() == 3) {		//for each word that is 3 characters long, check to make sure the input is rank/suite and create card.
						if (isValid(i, 3) == 1) {
							char input = '1';
							Card C = CreateCard(input, i[2]);
							temp.push_back(C);	//put the card into the card vector.
						}
					}
				}	//by here, you've parsed through the line

				word.clear();
				//if (temp.size() != 5) {
					//cout << word.str() <<  " This line does not contain a valid hand of cards." << endl;
				//}
				if (temp.size() == 5) {	//a valid hand of cards
					sort(temp.begin(), temp.end());	//sort the cards first
					Hand.insert(Hand.end(), temp.begin(), temp.end());	//add the temp, valid hand to the vector of hands.
				}
				temp.clear();	//clear temp for next line.
			}   
			iss.clear();	//clear the iss string stream for the next line
		}

		const vector<Card> Hands = Hand;	//feed this into the poker hand function

		if (Hand.empty()) {	//no valid hands of cards were read
			throw 25;
		}
	}
	
	ifs.close();
	return 0;
}

int Parser(vector<Card> &Deck, char *p) {
	ifstream ifs;
	ifs.open(p);

	if (!(ifs.is_open())) {
		throw 2;	//return 2 if no text file to open. Otherwise, you've opened it and you're ready to read.
		return 2;
	}
	if (ifs.is_open()) {
		string i;
		while (ifs >> i) {	//iterate through every word in the text file. This separates each word from the whitespaces
			if (i.size() == 2) {	//for each word that is 2 characters long, check to make sure there's a valid card def, then create card.
				if (isValid(i, 2) == 1) {
					Card C = CreateCard(i[0], i[1]);
					Deck.push_back(C);	//put the card into the card vector
				}
			}
			if (i.size() == 3) {		//for each word that is 3 characters long, check to make sure the input is rank/suite and create card.
				if (isValid(i, 3) == 1) {
					char input = '1';
					Card C = CreateCard(input, i[2]);
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
		cout << "Error: No valid poker hands were found. Valid card definitions are 2 or 3 characters long, listed rank then suite. Each card definition should be separated by a space, tab, or other form of white space. Each line in the file should hold 5 valid card definitions to represent a hand. The line may end either with a carriage return or the comment symbols '//'" << endl;
	}
}





