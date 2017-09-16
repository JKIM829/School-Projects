Jennifer Kim
Lab1

Outputs:

I used the cards.txt file from the course website and got the correct outputs. Then, I changed the file slightly to get rid of some “//“ at the end of the lines, to see whether my function read the line fully. This is why I use two string streams per line - one is to read through the line completely, and the next reads through the line until it sees a delimiter ‘/‘. One thing to note is that my parsing function ignores lines that do not have valid hand definitions. Every line is evaluated, and if 5 card definitions are stored in a temporary vector, then I sort that temp vector using STL sort and append it to the main vector<Card>. This way, I can skip sorting in the main function. Additionally, because I have this error check in the parse function, I can search for poker hands for every 5 cards, and add the poker hand definition for that hand to a string vector. Then, it’s easy to print the hands and poker hand definitions simultaneously, since each poker hand definition string corresponds to every 5 card vectors. 

Other error messages are the same as Lab0 - the Usage message returns 10, invalid files throw 2, and files with no valid hands throw 25. I checked this with echo %errorlevel% , which showed the correct return values for each of these cases.


Errors:

I encountered Error code C3869, which happened because I used vector_name.size instead of vector_name.size(). Other than that, I had an error at the beginning where it said C1010 “Did you forget to add #include “stdafx.h” to your source?” I added this to all my source files, and the error went away. I encountered this error in Lab0, but worked around it by disabling Visual Studio’s inclusion of the pre compiler. This time, I asked a TA and they told me to include this header file on each .cpp file. 



Below is my modified cards.txt file. I also used this ReadMe file as a test, and it returned only the correct hands. 

KD JD 6s 5s 3c // no rank (king high)

6H // not a hand (too few)

Qs QH	 JH Qc Jc // full house

6c 10s 9H  8s  7H // straight

AH Ks Js AD Ac // three of a kind

9D  6D 5D 8D 7D // straight flush

7s 8c 2s 5H 2c 
     
Kc 3s 3D 2D 7c 5c  // not a hand (too many)

4s 4H  4D As 4c  // four of a kind

KH   10H 3H 2H 8H // flush

9c QD 10c 10D 9s //  5d two pairs

3d qs 5d 9h As

