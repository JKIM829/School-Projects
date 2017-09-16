// Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Card.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])	//NOTE: I'm not calling the STL sort algorithm here because my parsing function already sorts the vectors before inserting it into the main vector Hand. 
{
	if (argc < 2 || argc >2) {
		UsageMsg(argv[0]);
		return 10;
	};

	try {
		vector<Card> Hand;
		char *pointer = argv[1];	//point to input
		int r = Parse2(Hand, pointer);	//run the parser NOTE: I sort the cards in this function using STL sort algorithm, so there's no need to call it from the main function
		vector<string> PokerHands = PokerHand(Hand);	//turn into hand definitions.
		int t = HandPrinter(Hand, PokerHands);	//this functions prints out the cards and hand per line
		return r;	//finally, if all goes well, should return 0.
	}

	catch (int r) {	//when things don't work
		ErrorMsg(r);	//prints out what's wrong
						//cout << "ERROR CODE " << r << endl;
		return r;
	};
}

