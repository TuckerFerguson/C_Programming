###OS Warmup Project

Author: Tucker Ferguson
Class: CS453 Section 2

Overview: This program parses output from the command ps augx continually until specified to stop. The desired piece of output being searched for is information regarding threading, specifically which tasks are multi-threaded.

Compiling and Using: To compile one should use the command "make" which due to our makefile handles compiling of files and creates up to date executable. After which the user should follow the command line arguments "ps-logger <sleep interval>".This will begin the process of showing multi verse non-multi threaded processes. Since the program functions on a continuous loop the user must use Ctrl-C to stop when desired.

Testing: Testing here was done with nested print statements ensuring that my program was parsing the correct information. Next I made sure values being calculated using the parsed information were correct by opening new processes on my node and ensuring my results would adjust accordingly.

Sources Used: Included backpack files as well as old programs from previous course CS-253 were taken advantage of here as well as piazza.

Known Issues: When compiled my program still has several warnings most of which are syntax specific. Inbetween the time I write this and submit the actual project hopefully these are all fixed.

README.md: this file
ps-sample.log: A sample output for "ps augx" command
ps-logger.c: skeleton code to get you started
Makefile: build file
readfile.c: shows how to read a text file in C
strings-ex4.c: shows how to parse a text file line by line
