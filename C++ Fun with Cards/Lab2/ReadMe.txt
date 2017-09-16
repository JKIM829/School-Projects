Jennifer Kim
Lab 2: Cards Decks & Hands

\\\\\\\\\\\\\\\\\
I. Inputs and Tests:

I first tested all input cases, with a bad/invalid command and echo %errorlevel% command:

1. If no command line arguments are given, then the user message prints and returns 10.

2. If there's only one command line, and it's '-shuffle', then the Error Message prints and returns 19.

3. If there's only one command line, and the text file couldn't be opened, then then Error Message prints and returns 2

4. If there are 2 arguments, and neither contain "-shuffle", then the Error Message prints and returns 23.

5. If there are 2 arguments, and one contains "-shuffle" but the other is not a valid file name, then the Error Message prints and returns 2.
	
6. If there are more than 2 arguments, then the Error Message prints and returns 27.

7. If the text file doesn't have enough (45) card definitions, then the Error Message prints and returns 71.

Otherwise, for valid inputs, the sorting (by hand, then by hand rank) works as specified.
This is the output for the command "lab2.exe lab2test.txt -shuffle":

This deck is shuffled.
This is the deck after dealing 9 hands:
9, D
8, C
10, D
K, D
8, S
5, H
K, C
10, D
K, C
3, C
Q, S
5, C
6, S
7, C
4, C
6, D
10, D
4, S
K, D
9, S
10, C
10, H
Q, H
J, C
Q, D
J, C
8, S
9, H
9, S
Q, H
8, C
Q, D
2, D
5, D
K, D
10, C
Q, S
7, S
3, H
9, S
7, S

These are the hands before sorting:
One Pair  3C 7C 9D 9H AD
No Rank  3H 5H 9D 10D KH
No Rank  2S 3S 8S 10S QC
No Rank  3H 4H 9S 10H JD
One Pair  3C 8S 9S QC QS
No Rank  2H 7C 9C JS AD
No Rank  2H 3C 6D 7H JS
No Rank  4D 5H 6C QC AC
No Rank  2S 6S 7S 9H AH

These are the hands after sorting:
No Rank  2H 3C 6D 7H JS
No Rank  2H 7C 9C JS AD
No Rank  2S 3S 8S 10S QC
No Rank  2S 6S 7S 9H AH
One Pair  3C 7C 9D 9H AD
One Pair  3C 8S 9S QC QS
No Rank  3H 4H 9S 10H JD
No Rank  3H 5H 9D 10D KH
No Rank  4D 5H 6C QC AC

These are the hands after sorting by poker rank:
No Rank  2H 3C 6D 7H JS
No Rank  3H 4H 9S 10H JD
No Rank  2S 3S 8S 10S QC
No Rank  3H 5H 9D 10D KH
No Rank  2S 6S 7S 9H AH
No Rank  2H 7C 9C JS AD
No Rank  4D 5H 6C QC AC
One Pair  3C 7C 9D 9H AD
One Pair  3C 8S 9S QC QS
Done

\\\\\\\\\\\\\\\\\\\\\\
II. Errors/Warnings:

1. C2672: "operator_surrogate_func' : no matching overloaded function found':
I fixed this error by including an equality operator for my Card structs.

2. C416: "operator <<'  must return a value':
I fixed this error by having my ostream operator return an ostream.

3. C2360: 'Initialization of 'p1' is skipped by 'case' label':
This occurred in my poker_rank function; I fixed this error by including brackets { } around each case in my switch statement.


\\\\\\\\\\\\\\
III. Extra Credit:

 a(8) is satisfied: my Load(char *p) method for the Deck throws an exception whenever the method can't open the file, which is then caught at the constructor. The constructor then throws it in the main function, so that my program can catch it and print the correct error message.
a(9) is also satisfied: I only use exceptions when the file can't be opened, which qualifies as an abnormal condition. Otherwise, my main program satifies normal conditions by checking argv and returning error messages when applicable. 

a(12): I Dereference 'this', but because 'this' is not zero, there's no access violation.
a(13): and a(14) applies: before I access an element of a vector, I make sure that the index is within the bounds of the vector.
a(15) is satisfied because I use vectors to hold card or hand objects instead of fixed size containers (like arrays).

a(16): I used the debugger when working on the poker_rank function. There were cases where 2 two_pair hands weren't evaluating correctly; I figured out that this was because I didn't consider the case where the fifth card (card that's not in a pair) was in the middle of the vector. I only counted for cases where it was at the end or beginning of the vector. It was helpful to print messages on the screen during debugging, especially for each of the cases.

b(10): This condition is fulfilled by my program.
b(11): This condition is fulfilled by my program: see Hand constructor for example
b(12): This condition is fulfilled by my program: see Deck constructor for example.

b(31): This is done for Card.h, Hand.h, and Deck.h





