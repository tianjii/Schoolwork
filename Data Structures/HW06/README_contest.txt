HOMEWORK 6 CONTEST: INVERSE WORD SEARCH


NAME:  Skylar Sang


OPTIMIZATIONS:
What did you do?

Truthfully there weren't many optimizations that made noticable differences in run time once I got the code to start working.

One initial decision that impacted my entire implementation was that I decided to create boards on the stack instead of the heap since it takes less time for the program to find structures on the stack.

I found that using bools and if statements inside of my function barred off functionality that wasn't needed (e.g. testing if a word could fit in a direction before attempting to change spaces)

In my function that tests if a board is completed I tested if the minus words were in the board before filling the blank spacess. Puzzles siuch as puzzle3 would give me solutions that fit all the words but with blank spaces, and filling those with letters took too much time when the board should have been marked beforehand.



TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?

Program was very fast in all test cases except for puzzle 8 where it took a bit over 3 seconds to finish.
My new test cases were focused on speed once I was certain the code worked. I extended puzzle 8 by adding one more row and column.
 Puzzle 8 took significantly longer to finish than it did before and wouldn't even finish within a remotely reasonable time.
 It shows that my code can't really handle anything larger than puzzle 8.