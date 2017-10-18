HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  Skylar Sang


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Piazza - instructor (Mersenne Twister)
Kirsten Pilla - debugging

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
Maps are nested, but the logn computations add together because the code looks through one map, then looks through the next separately. Notation of looking through nested maps would just be O(logn).
Maps would only have the unique words as keys. Using the order notations that I found in the section below, since is the greatest of all the values, the order notation of the code would be (nlogm) for any amount of print and generate commands. (would just be multiples of nlogm, so the order notation would stay the same).



n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word

How much memory will the map data structure require, in terms of n, m,
w, and p (order notation for memory use)?

m*p^w - outermost map will have m words in it, with average p words in each subsequent nested map.


What is the order notation for performance (running time) of each of
the commands?

Load : O(n*logm+logp*(W-1)) -> O(nlogm) m >= p
Print :  O(p*logm+logp*(w-1)) -> O(plogm)
Generate : O(s*p*logm+logp*(W-1)) -> O(s*p*logm) s is the number of words to generate 


EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


