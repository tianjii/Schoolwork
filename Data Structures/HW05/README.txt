HOMEWORK 5: DSRADIO SONG GROUPS


NAME:  < Skylar Sang >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Kirsten Pilla (Debugging / checking code)

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 16 >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of s = the number of songs in the library,
g = the number of song groups, a = the average number of songs by the same 
artist, and l = the average length of song groups.

AddSongToLibrary O(S)


GroupExists O(G)

AddToGroup O(L)

MakeGroup O(G)

PrintGroupRewind O(L)

PrintLongestGroupRewind O(L^2)

RemoveGroup O(G+L)

DeleteAllSongGroups O(G*L)

RemoveFromGroup O(L)

PrintGroupMarathon O(A)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

I used gdb and Dr. Memory to debug my program, but Dr. Memory helped the more because it executed and quickly showed the source of the problem in the error backtraces. I had actually forgotten to adjust a few of my functions for the corner cases where the group or list would be empty, and it wasn't until I made more and more tests with Dr. Memory that I was able to figure out that I was missing these cases. By changing the input file to what I wanted I was able to better keep track of my nodes and where my songs were going.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

Is addition of different values in O notation valid? (e.g  the O(G+L) from above)



