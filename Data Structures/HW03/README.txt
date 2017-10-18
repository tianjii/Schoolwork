HOMEWORK 3: MATRIX CLASS


NAME:  < insert name >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
Coen Valk: error checking
Kirsten Pilla: error checking

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 > 



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get O(1)

set O(1)

num_rows O(1)

get_column O(N)

operator<< O(M*N)

quarter O(M*N)

operator== O(M*N)

operator!= O(M*N)

swap_rows O(N)

rref (provided in matrix_main.cpp) O(M*M*N)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I started with GDB in both Cygwin and WSL to watch and print variables that were not changing correctly. Memory bugs were fixed with Dr. Memory only after any segfaulting or aborts were corrected.

I first tested the corner cases of the Matrix class in a separate file so that I could isolate a member function and only work on one matrix at a time. Some corner cases included Matrixes with 0 rows and columns, as well as some with extreme dimensions. (i.e rows << cols or vice versa)


EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.

I did implement the extra credit.

No matter what the original size, new matrix sizes are absolute

Order Notation:
O(M*N) where M = new_rows
		 and N = new_cols



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

