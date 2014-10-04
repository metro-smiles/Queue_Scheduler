Queue_Scheduler
===============

A Scheduling system for Router Queues

The Project consists of the following three source files :-
	1. MM1_1.cpp : This is the source file, which implements Part-1 of the project. It takes in the Case Number as a command-line argument and displays the statistic values.
	2. NetworkMM1_2.cpp : This is the source file, which implements Part-2 of the project. It takes in the Case Number as a command-line argument and prompts the user for appropriate parameter inputs and displays the corresponding statistics.
	3. MG1_3.cpp : This is the source file, which implements Part-3 of the project. It takes in the the Number of arrivals and the Seed Value as input and displays the corresponding statistics.

A slightly detailed description about the implementation, can be found in the report.	
	
Instructions for running the source codes :-
1. Place all the 3 Source files in the same directory, including the Makefile and type "gmake" from the command-line. This will compile all the source files.
2. Now inorder to run the first part, type in "./part1 <Case Number>", where the Case Number is between 1, 2 and 3, respectively for the 3 cases asked in the question.
   Note, that the parameter values have been initialized from within the code (i.e. lambda, mu, etc.)
3. Inorder to run the second part, type in "./part2 <Case Number>", where the Case Number is between 1 and 2, respectively for the 2 cases asked in the question.
   Note, that the parameter values are to be supplied by the user. So, the code will prompt the user for the necessary parameter values. Also, note that part 2 of 
   the program (5-queue system) will run for cases where there is no feedback path. Although, it can be easily extended to accomodate this change.
4. Inorder to run the third part, type in "./part3 <Number of arivals> <Seed Value>". The other parameters, such as lambda, etc. have been initialized from within the 
   source code.

