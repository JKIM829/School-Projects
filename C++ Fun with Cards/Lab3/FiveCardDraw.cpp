#include "stdafx.h"
#include "FiveCardDraw.h"


//Declare helper methods here. 
void Increment_Decrement(vector<shared_ptr<Player>> &copy, vector<shared_ptr<Player>> &real);
bool sort_player_ptrs(shared_ptr<Player> p1, shared_ptr<Player> p2);
int pairHelper(vector<Card> &cards);
bool poker_rank(const Hand &h, const Hand &h2);

//helper member function to reset the main and discard deck.
void FiveCardDraw::resetDeck() {
	discard_deck.resetDeck();
	mainDeck.resetDeck();
	Card C;
	for (int i = 0; i < 4; ++i) {
		for (int j = 2; j < 15; ++j) {
			C.rank = Ranks(j);
			C.suite = Suites(i);
			mainDeck.add_card(C);
		}
	}
}
//helper member function to see who wants to leave the game:
bool FiveCardDraw::WannaLeave() {
	string s; 
	bool quitter = false;
	while (true) {
		cout << "Do any players wish to leave the game? Enter Y for Yes or N for No." << endl;
		cin >> s;
		if (s.compare("Y") == 0) {
			cout << "Who wants to leave? Enter one name at a time, and wait for verification." << endl;
			quitter = true;
			break;
		}
		if (s.compare("N") == 0) {
			return true;
		}
	}
	s.clear();

	while (quitter) {
		cin >> s;
		if (s.compare("N") == 0) {
			quitter = false;
			return true;
		}
		shared_ptr<Player> p = find_player(s);
		vector<shared_ptr<Player>>::iterator it;
		if(p != 0){
			it = find(players.begin(), players.end(), p);
			if (it != players.end()) {
				makePlayerFile(*it);
				players.erase(it);
				cout <<  s << " has left the game. Enter another player, or enter N to continue the game." << endl;
			}
			else {
				cout << "The player " << s << " is not a valid player. Enter a valid name, or enter N for no." << endl;
				continue;
			}
		}
		if (p == 0) {
			cout << s << " is not a player in this game. Please enter a valid player, or N to continue." << endl;
		}
	}
	return false;
}

bool FiveCardDraw::WannaJoin() {
	stringstream temp;
	string s;
	string input;
	cout << "Are there any new players who wish to join? Enter N for no, or enter the player's name." << endl;
	while (true) {
		cin >> input;
		if (input.compare("N") == 0 || input.compare("no") == 0 || input.compare("n") == 0 || input.compare("No") == 0) {
			return true;
			break;
		}
		try {
			add_player(input);
		}
		catch (...) {
			cout <<input << " is already a player. Enter another name for the new player, or enter N to continue the game." << endl;
			continue;
		}
		cout << "Player " << input << " has joined!" << endl;
		cout << endl;
		cout << "Are there any more players who wish to join? Enter N for no, or enter the player's name." << endl;
		input.clear();
	}
	return false;
}

void FiveCardDraw::finalPlayer(shared_ptr<Player> &p) {
	makePlayerFile(p);
	players.clear();
}


//make the player file
void FiveCardDraw::makePlayerFile(shared_ptr<Player> p) {
	ofstream outfile;
	outfile.open((*p).Name);
	outfile << (*p).Name << endl << (*p).handsWon << endl << (*p).handsLost << endl;
}

FiveCardDraw::FiveCardDraw() {
	dealer = 0;
	Card C;
	resetDeck();
}

int FiveCardDraw::before_turn(Player &p) {
	string s;
	string reader;
	stringstream input;
	string directions1 = "Which card would you like to discard? Enter 0 if you do not want to discard any cards.";
	string directions2 = " Else, enter the positions of the cards, one at a time. For example, entering 1 removes the first card of your hand.";
	
	
	vector<Card> hand = p.hand.getCards();
	if (hand.empty()) {
		return 10;
	}
	vector<int> positions = {};
	vector<int>::iterator it;
	int pos = 999;

	while (true) {
		cout << endl << "Player " << p.Name << endl;
		cout << "Current Hand: " << p.hand << endl;
		cout << directions1;
		cout << directions2 << endl<<endl;

		cin >> reader;
		try {
			pos = stoi(reader);
		}
		catch (...) {
			cout << "Gibberish detected. Please enter a valid index." << endl;
			continue;
		}
			if (p.hand.size() == 0  ) {
				cout << "You have no more cards to discard. Moving on..." << endl;
				return 0;
			}
			if (pos > p.hand.size() || pos < 0) {
				cout << pos << endl;
				cout << "You've entered an invalid position. Please try again. " << endl;
				continue;
			}
			
		//by here, you should have read through the input:

		if (pos == 0) {
			cout << "No cards were removed." << endl;
			cout << endl;
			return 0;
		}
		int remove = pos-1;
		discard_deck.add_card(hand[remove]); //add the card to the discard_deck
		p.hand.remove_card(remove);	//remove the card from the player's hand
		cout << "Removed: " << ToStringRanks(hand[remove].rank) << ToStringSuites(hand[remove].suite) << endl;	
		cout << endl;
		}

return 0;

}

int FiveCardDraw::turn(Player &p) {
	int current = p.hand.size();
	int needed = 5 - current;
	while (needed > 0) {
		if (mainDeck.size() > 0) {
			p.hand.push(mainDeck.pop());
		}
		else if (mainDeck.size()==0 && discard_deck.size() > 0) {
			discard_deck.shuffle();
			p.hand.push(discard_deck.pop());
		}
		else {
			return 10;
		}
		--needed;
	}
	return 0;
}

int FiveCardDraw::after_turn(Player &p) {
	cout << "Player " << p.Name << " currently holds these cards in their hand: " << p.hand.asString() << endl;
	p.hand.setHandRank();
	cout << p.Name << "'s poker rank is " << HandRanks_toString(p.hand.getHandRank()) << endl << endl;
	return 0;
}

int FiveCardDraw::before_round() {
	mainDeck.shuffle();
	if (players.size() == 0) {
		throw 200;
	}
	if (players.size() * 5 > mainDeck.size()) {
		return 50;
	}
	//begin with player just past dealer, and deal cards.
	for (int j = 0; j < 5; ++j) {
		for (int i = 1; i < players.size()+1; ++i) {
			(*players[(i + dealer) % players.size()]).hand.push(mainDeck.pop());
		}
	}
	int temp;
	for (int i = 1; i < players.size()+1; ++i) {
		temp = before_turn(*(players[(i + dealer) % players.size()]));
		if (temp != 0) {
			return temp;
		}
	}
	return temp;
}

int FiveCardDraw::round() {

	if (players.size() == 0) {
		throw 200;
	}

	for (int i = 1; i < players.size()+1; ++i) {
		int t = turn(*players[(i + dealer) % players.size()]);
		if (t != 0) {
			return t;
		}
		int at = after_turn(*players[(i + dealer) % players.size()]);
		if (at != 0) {
			return at;
		}
	}
	return 0;
}

int FiveCardDraw::after_round() {
	if (players.size() == 0) {
		throw 200;
	}
	vector<shared_ptr<Player>> copy_players = players;
	for (size_t i = 0; i < copy_players.size(); ++i) {
		if ((*copy_players[i]).hand.size() != 5) {
			throw 600;
		}
		(*copy_players[i]).hand.setHandRank();
	}
	//sort the copy players
	sort(copy_players.begin(), copy_players.end(), sort_player_ptrs);

	//increment hands won/lost in the real players
	Increment_Decrement(copy_players, players);

	//prints out players from highest hand to lowest hand.
	for (vector<shared_ptr<Player>>::reverse_iterator it = copy_players.rbegin(); it != copy_players.rend(); ++it) {
		(*(*it)).hand.sortHand();
		cout << (*(*it));
	}
	cout << endl;

	//main deck and discard deck are reset. Discard_deck has 0 cards, main deck has 52.
	resetDeck();

	//clear all the hands of the current players:
	for (vector<shared_ptr<Player>>::iterator it = players.begin(); it != players.end(); ++it) {
		(*(*it)).hand.clearHand();
	}
	//ask if players want to leave or join. If helper methods didn't finish successfully, they'll return false.
	bool leave = WannaLeave();
	bool join = WannaJoin();
	if (!(leave && join)) {
		return 10;
	}
	if (num_players() < 2) {
		finalPlayer(players[0]);
		cout << "Only 1 player in game." << endl;
	}
	(++dealer) % (players.size()-1);
	return 0;
}

////HELPER METHODS:

//Helper method that searches through the sorted copy players, and increm/decrem the real players' won/lost count based on hand rank
void Increment_Decrement(vector<shared_ptr<Player>> &copy, vector<shared_ptr<Player>> &real) {
	vector<shared_ptr<Player>>::iterator it;
	for (vector<shared_ptr<Player>>::reverse_iterator rit = copy.rbegin(); rit < copy.rend(); ++rit) {
		if (!sort_player_ptrs(*rit, (copy.back()))) {	//if it has the highest hand, increment the handwon
			it = find(real.begin(), real.end(), *rit);	//find the player by name
			if (it != real.end()) {
				++(*(*it)).handsWon;	//and increment that player's HandsWon 
			}
		}
		else {
			it = find(real.begin(), real.end(), *rit);	//this means they didn't have the highest hand, so increment lost.
			if (it != real.end()) {
				++(*(*it)).handsLost;
			}
		}
	}
}

//Helper method to sort players based on their hand rank
bool sort_player_ptrs(shared_ptr<Player> p1, shared_ptr<Player> p2) {
	if (p1 == 0) {
		return false;
	}
	if (p1 != 0 && p2 == 0) {
		return true;
	}
	return poker_rank((*p1).hand, (*p2).hand);
}

//helper method to help determine where pairs in a hand are
int pairHelper(vector<Card> &cards) {	//returns the index of the first card in a pair
	for (size_t i = 0; i < (cards.size() - 1); ++i) {
		if (cards[i].rank == cards[i + 1].rank) {
			return i;
		}
	}
	return 0;
};

//helper method to determine which handrank is higher
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
		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
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
			for (size_t i = v1.size() - 1; i > 0; --i) {
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
					if (v1[0].rank == v1[1].rank && v1[2].rank == v1[3].rank) {	//5th card in last position for v1
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