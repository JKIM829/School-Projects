Jennifer Kim
Lab 3

///Tests///

1. 
Entering inputs with less than 2 players will prompt the usage message.

2.
Entering any inputs with the first being FiveCardDraw will prompt the unknown game error message.

3. 
For games with 2 - 10 players, the game proceeds normally. Each player is rotated according to dealer position (as stated in directions) and before the round, they're given the choice of discarding cards. If the input is not a number, an error message will print. If the input is not in a valid range, and error message will print. If the player has no more cards to discard, the game proceeds to call on the next player to discard their cards.

The round function prints out the players and their hands and poker ranks.

The After round function prints out who won, who lost, and asks if any players want to leave.
If an unknown player player tries to leave, the invalid player message prints, and the program asks again who wants to leave.
Any player who leaves has their data saved in a text file.
Afterwards, the program asks who wants to join. If a current player tries to join again, an error message will print, and the program asks again who wants to join.

Finally, if there are less than 2 players, the game makes a player file for the last player, clears the vector of player pointers, and closes successfully.

4.
I tested to make sure the Load function for players works. When repeated, players have saved memory of handsWon and handsLost.

///ERRORS///

I ran into the problem of all of my header files suddenly becoming undefined -> I forgot to use the #ifndef protection on them.


///Example/// (I tried a game with previous players - their handswon/handslost should be more than 1 initially)

C:\Users\jennifer.kim_000\Documents\Visual Studio 2015\Projects\Lab3\Debug>lab3.exe FiveCardDraw Harry Ron H
ermione

The game FiveCardDraw has started. Current players:
Harry
Ron
Hermione


***** BEFORE ROUND *****


Player Ron
Current Hand: KC 4C 4H 5H KH

Which card would you like to discard? Enter 0 if you do not want to discard any cards. Else, enter the posit
ions of the cards, one at a time. For example, entering 1 removes the first card of your hand.

lsjdf
Gibberish detected. Please enter a valid index.

Player Ron
Current Hand: KC 4C 4H 5H KH

Which card would you like to discard? Enter 0 if you do not want to discard any cards. Else, enter the posit
ions of the cards, one at a time. For example, entering 1 removes the first card of your hand.

0
No cards were removed.


Player Hermione
Current Hand: 3H 2H 6S 2C AD

Which card would you like to discard? Enter 0 if you do not want to discard any cards. Else, enter the posit
ions of the cards, one at a time. For example, entering 1 removes the first card of your hand.

1
Removed: 3H


Player Hermione
Current Hand: 2H 6S 2C AD

Which card would you like to discard? Enter 0 if you do not want to discard any cards. Else, enter the posit
ions of the cards, one at a time. For example, entering 1 removes the first card of your hand.

4
Removed: 2C


Player Hermione
Current Hand: 2H 6S 2C

Which card would you like to discard? Enter 0 if you do not want to discard any cards. Else, enter the posit
ions of the cards, one at a time. For example, entering 1 removes the first card of your hand.

0
No cards were removed.


Player Harry
Current Hand: 7H 10S KS 10C 10H

Which card would you like to discard? Enter 0 if you do not want to discard any cards. Else, enter the posit
ions of the cards, one at a time. For example, entering 1 removes the first card of your hand.

3
Removed: KS


Player Harry
Current Hand: 7H 10S 10C 10H

Which card would you like to discard? Enter 0 if you do not want to discard any cards. Else, enter the posit
ions of the cards, one at a time. For example, entering 1 removes the first card of your hand.

10
10
You've entered an invalid position. Please try again.

Player Harry
Current Hand: 7H 10S 10C 10H

Which card would you like to discard? Enter 0 if you do not want to discard any cards. Else, enter the posit
ions of the cards, one at a time. For example, entering 1 removes the first card of your hand.

0
No cards were removed.


***** ROUND *****

Player Ron currently holds these cards in their hand:  KC 4C 4H 5H KH
Ron's poker rank is No Rank

Player Hermione currently holds these cards in their hand:  2H 6S 2C 9C AC
Hermione's poker rank is One Pair

Player Harry currently holds these cards in their hand:  7H 10S 10C 10H 7C
Harry's poker rank is No Rank

***** AFTER ROUND *****

Player: Hermione Hands won: 2 Hands lost: 3 Hand: 2C 2H 6S 9C AC

Player: Ron Hands won: 0 Hands lost: 4 Hand: 4C 4H 5H KC KH

Player: Harry Hands won: 2 Hands lost: 2 Hand: 7C 7H 10C 10H 10S


Do any players wish to leave the game? Enter Y for Yes or N for No.
Y
Who wants to leave? Enter one name at a time, and wait for verification.
Harry
Harry has left the game. Enter another player, or enter N to continue the game.
Ron
Ron has left the game. Enter another player, or enter N to continue the game.
Hermione
Hermione has left the game. Enter another player, or enter N to continue the game.
N
Are there any new players who wish to join? Enter N for no, or enter the player's name.
Draco
Player Draco has joined!

Are there any more players who wish to join? Enter N for no, or enter the player's name.
N
Only 1 player in game.
Not enough players. Game over!

C:\Users\jennifer.kim_000\Documents\Visual Studio 2015\Projects\Lab3\Debug>



