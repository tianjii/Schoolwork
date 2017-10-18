HOMEWORK 1: AIRLINE SEATING


NAME:  Skylar Sang


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
Piazza, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Coen Valk, lecture notes. (For help understanding pass-by-referencing in functions).

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8



EXPLANATION OF REMOVING PASSENGERS FROM UPGRADE LIST:
Describe the data structure you used to represent the upgrade lists,
and how you removed passengers from these lists.

Packed passengers to be upgraded into two different vectors one for each type of upgrade seat classes.

Under the assumption that the upgrade would only once at the end of the file

In order to remove the passenger ID from the list:
  1. Iterated through to find the index of ID.
  2. Packed ID's that weren't at that index into a temporary vector.
  3. Replaced contents of upgrade vector with the temporary vector.

  Now that I think of it, the first two steps could have been only one.


MISC. COMMENTS TO GRADER:  
Optional, please be concise!

For reference how would you have removed an item from the upgrade vector?


