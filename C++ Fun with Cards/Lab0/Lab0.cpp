// Lab0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Card.h"

using namespace std;


int main(int argc, char *argv[])
{
	if (argc < 2 || argc >2) {
		UsageMsg();
		return 10;
	};
	try {
		vector<Card> Deck;
		char *pointer = argv[1];	//point to input
		int r = Parser(Deck, pointer);	//run the parser
		int dummy =CardPrinter(Deck);	//run the printer
		return r;	//finally, if all goes well, should return 0.
	}
	catch (int r) {	//when things don't work
		ErrorMsg(r);	//prints out what's wrong
		//cout << "ERROR CODE " << r << endl;
		return r;
	};
}

