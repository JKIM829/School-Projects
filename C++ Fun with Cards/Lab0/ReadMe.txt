Jennifer Kim
Lab 0

USAGE AND OUTPUTS:

When the program lab0.exe is run from the command terminal, the first message it outputs is the UsageMsg() function, which specifies the program name and what kind of inputs is acceptable. If the program detects more than 1 input or no input, then it will print out this message.

If one input is given, then the program checks to make sure it's a .txt file that's accessible. If the input cannot be opened, then an error message is printed stating that the file couldn't be opened. In my first test, I labeled the card_def.txt file wrongly, so that the true name was "car_def.txt.txt". Accordingly, the program printed out the correct error that the input could not be opened.

If you used the command line 'lab0.exe 4' , it will not recognize the input as a file that can be opened, so you run into the error message of "file can't be opened".

If the input can be opened, the program runs as directed and outputs a string of Card objects, by rank and suite per line. If there are no valid card definitions in the file.txt, then an error message is printed stating that there were no valid card definitions in the input file. Valid card definitions are 2 or 3 characters long, given by rank (2, 3, 4, 5, 6, 7, 8, 9, 10, j or J, q or Q, k or K) then suite (d or D, s or S, h or H, c or C). Each card definition needs to be separated by a space, a tab, or a new line. 

Finally, if all goes well, the program will print out all cards detected in the file.

I ran these trials with "lab0.txt" file, which held valid card definitions as well as invalid ones. I also tried using this ReadMe file, and the only detections were when I used the word 'as', which showed up as Ace of Spades.


ERRORS:

Initially, I had over 40 errors when I first compiled the code. Most said that I needed to add ; after }, or similar. I found that after I removed #include "stdafx.h" in the Card.cpp file, these errors went away and the program compiled normally. I believe that this is due to Lab0.cpp already including the precompiled header program.

Other than that, I had a "Incomplete type not allowed" error in the header file, which was due to my ordering of the functions. I accidentally defined the card struct after the CardCreator() function. When I ordered the header file as Rank enums -> suite enums -> card struct -> all other functions, this error went away.



(OPTIONAL, CAN SKIP) STRUCTURE: I tried to comment a reasonable amount to make the program clear, but here's an overview of the code.

The Card.cpp file has a Parser(vector<Card> &Deck, char *p) method that returns either 0 if the run was successful, or some other integer if there was a failure. It uses several helper methods:
First, it supplies an ifstream with the name of the input file, given by the pointer char * p. If the file cannot be opened, it throws an error code. Otherwise, it opens the file and iterates over each word string in the file (so it skips whitespaces). 
For each word, there are 3 helper methods. First, after checking that the size of the word is 2 or 3 characters long, it feeds the word into the isValid method, which checks that the first (and second if size = 3) is an allowable rank and the last character is an allowable suite. If this is successful, then the method returns and the next method is called. CardCreator creates a card given a correct rank and suite char. It's guaranteed to have a valid rank and suite char because of the isValid method. Otherwise, in case my previous attempts of validation didn't work, when I use the toString method to print, the card will say "Error, Unknown Suite". The Card object that CardCreator returns is then pushed onto the card vector. 
After every word is read and evaluated, the Parser checks if the vector<Card> is empty. If it is, then it returns an error that means no valid card definitions were found in the input.
Otherwise, it closes the stream and returns 0. 



