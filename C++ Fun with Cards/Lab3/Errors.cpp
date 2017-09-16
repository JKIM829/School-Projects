#include "stdafx.h"
#include "Errors.h"

int ErrorMsgs(int e) {
	if (e == 97) {
		cout << "Error: Invalid index " << endl;
	}
	if (e == 113) {
		cout << "Exception: instance_not_available " << endl;
	}
	if (e == 117) {
		cout << "Exception: game_already_started " << endl;
	}
	if (e == 137) {
		cout << "Exception: unknown_game" << endl;
	}
	if (e == 179) {
		cout << "Exception: already_playing" << endl;
	}
	if (e == 151) {
		cout << "Exception: no_game_in_progress" << endl;
	}
	if (e == 200) {
		cout << "Error: no players in the game" << endl;
	}
	if (e == 600) {
		cout << "Error: not enough cards in hand" << endl;
	}
	return e;
};

//int ErrorMsg(Errors err) {
//	int e = (int)err;
//	if (e == 97) {
//		cout << "Error: Invalid index " << endl;
//	}
//	if (e == 113) {
//		cout << "Exception: instance_not_available " << endl;
//	}
//	if (e == 117) {
//		cout << "Exception: game_already_started " << endl;
//	}
//	if (e == 137) {
//		cout << "Exception: unknown_game" << endl;
//	}
//	if (e == 179) {
//		cout << "Exception: already_playing" << endl;
//	}
//	if (e == 151) {
//		cout << "Exception: no_game_in_progress" << endl;
//	}
//	if (e == 200) {
//		cout << "Error: no players in the game" << endl;
//	}
//	if (e == 600) {
//		cout << "Error: at least one player does not have enough cards in their hand." << endl;
//	}
//	return e;
//}