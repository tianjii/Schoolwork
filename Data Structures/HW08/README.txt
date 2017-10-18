HOMEWORK 8: B+ TREES


NAME:  Skylar Sang


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

None.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  11


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

I mostly used Dr. Memory for this assignment because it was easy to see the trace and at which line # the error occurred.
In order to debug effectively I prioritized the print sideways function, which let me visualize how the nodes were grouped.
I tested the corner cases by printing out different sized trees and comparing the results to what I saw on the online simulation. If it was different then I'd have to take apart my code to find out what was wrong. Usually the problems arose from the nodes being split with incorrect iterators.




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

