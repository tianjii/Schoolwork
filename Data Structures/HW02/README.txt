HOMEWORK 2: LEAGUE OF LEGENDS CLASSES


NAME:  SKYLAR SANG

COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Coen Valk, stackoverflow (type casting)

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  7



DESCRIPTION OF 3RD STATISTIC: 
Please be clear & concise!  What is your hypothesis for the creation
of this statistic?

In League of Legends and similar games characters commonly labeled early, mid, or late game heroes.
By taking the time stamps of each event, setting the last event as the unofficial "end of the game," I was able to divide the game into three equal sections, allocating a champion's kills and deaths in the proper time slots. Based on the KDR during each time period I made an educated guess on what time of the match a character performs best. 


RESULTS FROM 3RD STATISTIC:
Paste in a small amount of sample output into this file, or list the
file names of sample input & output included with your submisssion.
Describe what is interesting about your statistic on this data.
Please be concise!

Based on the divided KDRs, the program determines when the champion historically performed best. As you can see, there are certain champions that have done significantly better in the early stages of the game, while eventually falling off later in the game. 


There are other factors such as player skill and the champion choices of the opposing teams (e.g. some early game champions may be better than other early ones). 



-------------------------

CHAMPION NAME       EARLY   MID  LATE   SCALING
Garen                0.50  2.50  2.00   MID GAME    
Olaf                 1.16  1.10  0.87   EARLY GAME  
Warwick              1.86  1.48  1.04   EARLY GAME  
Tryndamere           1.03  0.90  0.98   EARLY GAME  
Amumu                1.06  1.25  0.99   MID GAME    
Rammus               1.32  1.22  0.78   EARLY GAME  
Karthus              0.97  0.92  0.84   EARLY GAME  
Draven               1.09  1.13  1.26   LATE GAME   
Nunu                 1.06  1.05  0.54   EARLY GAME  
Cassiopeia           0.88  1.39  1.36   MID GAME    
Xerath               1.28  1.56  1.65   LATE GAME   
Hecarim              1.19  1.53  1.12   MID GAME    
Corki                1.18  1.14  1.40   LATE GAME   
Kalista              1.42  1.33  1.22   EARLY GAME  
Varus                1.23  0.90  1.28   LATE GAME   
Blitzcrank           0.84  0.62  0.55   EARLY GAME  
Pantheon             1.66  1.22  1.01   EARLY GAME  
Anivia               1.31  1.40  1.06   MID GAME




MISC. COMMENTS TO GRADER:  

In my code, if any two KDRs were equal, I set the scaling to "MID GAME" to suggest that the character is balanced.

