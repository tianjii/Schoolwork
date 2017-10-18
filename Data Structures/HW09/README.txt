HOMEWORK 7: MINIBLAST


NAME:  Skylar Sang


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cppreference.com for converting strings to char* using .c_str()
stackoverflow for hashing function



Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8


HASH FUNCTION DESCRIPTION

Hashing Function made by Paul Larson, researcher at Microsoft
Found in multiple sources in a variety of forms, but this is the one that I used.
Implemented with salt being 0

source: http://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map

unsigned hash(const char* s, unsigned salt)
{
    unsigned h = salt;
    while (*s)
        h = h * 101 + (unsigned) *s++;
    return h;
}






HASH TABLE IMPLEMENTATION
Each slot in the top level vector contains a pair. This pair has the string kmer 
as the first component, with a vector of ints as the second which represent the seed position. If the kmer is hashed
and the spot is empty (i.e. the vector is empty), that spot takes in the kmer and the first position. If the spot is occupied, 
the program does linear probing by first checking if the current spot has a kmer that matches the inserting key, pushing back the 
new seed position if it does match or incrementing the index and testing the next spot if it does not match.

When query is called, once the index is found and incremented to find the matching kmer pair, apply a search in the genome using e
ach int in the vector of ints as seed positions.


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the map data structure require (order notation for memory use)?
There are L-k kmers in the data structure, so O(L-k);


What is the order notation for performance (running time) of each of
the commands?

Hash - O(1)
Fill - fills L-k #of kmers of k size: O(k(L-k))
Resize - finds each node and insert it into new table: 
	For each unique key, the vector of ints is copied, so essentially all values are being copied over.
	The hash function is O(1)
	Resize is essentially O(L-k)

Query - Hash and find index O(1);
		Test vector of ints for n number of spots that start with the kmer
		For p spots, find query in genome and test q letters
		Query is O(pq)


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


