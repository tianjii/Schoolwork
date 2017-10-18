HOMEWORK 6: INVERSE WORD SEARCH

Summary of Recursive Algorithm for Github:
Note: Although this is an inverse word search, this solution is based off of how I solve normal word searches: by looking for the first letter

We are given width and height and a list of good words and bad words that we separate into different vectors.
It does not matter which word is searched for first, so we can go down the list of words in a linear fashion. The good words are recursively fit into a board while the bad words are checked for after the board is completed.

For inserting a word: 
The most important function in the entire code is called "setboard()," which is passed in parameters for a word and a board object. This is the recursive function

The primary loop involves checking each square on the board, if the square is empty or the contained letter matches the first letter in the word it is valid starting spot. 

Directional Analysis:
The length of the word is checked against the size of the board in 4 cardinal directions to make sure that it can even fit before testing that direction. Diagonal tests are just combinations of those directions. These tests aren't necessary but prevent the program from doing futile tasks.

If it can fit in a direction, the program loops through the spaces in that direction for the length of the word. If an existing letter does not match the letter it is testing nothing will happen. If it reaches the end of the word with no errors the setboard() function will be called recursively, being passed in the next word in the list along with a copy of the board object that contains the previous word in it. 

Final checks:
Once all words are fit into the board empty spaces are filled in with every valid letter of the alphabet, each letter requiring a new board. Those boards are then passed through a function that checks to see if words that should not be there are present in the board. If there are no bad words in a board it will be passed into a vector of board objects to be printed later.


NAME:  Skylar Sang


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

None

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  16-20


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?

Setboard function:
Going through each point in grid to check valid points - R*C (Row * Col)
Testing in 8 directions for each word - 8^W (# of Words)

Everything else has a smaller notation so the order notation is O(R*C*8^W)



TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?

Puzzles 1-7 were all less than 0.04 seconds, puzzle 8 took a bit over 3 seconds. Times decreased when only finding one solution as expected.

MISC. COMMENTS TO GRADER:  
Optional, please be concise!


