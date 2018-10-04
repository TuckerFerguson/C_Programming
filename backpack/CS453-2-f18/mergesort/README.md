# Project Number/Title {#mainpage}

* Author: Tucker Ferguson
* Class: CS453 [Operating Systems] Section 2

## Overview

This is a program originally contained methods for a serial merge sort, insert sort as well as 
some additional functionality of customizing amount of elements to be sorted via command line. 
We were asked to build upon this by implementing a thread safe parallel mergesort. 

## Manifest

INCLUDED FILES:

 * Makefile
 * mergesort.c
 * mergesortTest.c
 * timing.c
 
## Building the project

All project files should be in the same directory.

From the directory containing the .c source code, make the project:
    $ make

Navigate to directory named "multi-threaded"

Run the project using exectuable:
    $ ./mergesort  <input size> <number of threads> [<seed>] 



## Features and usage

The usage is quite self explanitory with the user being able to pass in the input size of amount of 
characters to sort, next is the number of threads you would like to utilize. Followed by an optional
argument of seed which dictates your random numbers generated to populate the array.


## Testing

I tested heavily with print statements and left a few in the code to atleast show my thought process. I had a
good fundimental understanding of what was suppose to be done in this project just could not get the pieces to fit.
I also made sure that there was no overwriting of memory to my best ability.

Along with this I often changed the size of elements I was entering to smaller more managable numbers. I 
printed out the members of the array as well as where I was partitioning it. Which all matched up.
The issue I could not get passed was failing towards the end elements, with typically a 0 comparison resulting 
in failed case. 




### Known Bugs

The program works fine when passing in one or two threads. With three working as well up until very large amounts of
elements were being passed in. After that the elements were failing to sort properly with the sub arrays being sorted
but merging improperly. I truthfully tried very hard to fix this and ended up running out of time unfortunately.

## Reflection and Self Assessment

Many of my testing methods and errors I often encountered are listed in the testing section but I will
go into more detail. I often had segfaults usually due to not handling the memory allocation properly but got this
fixed. Next I had trouble figuring out how to pass a struct into pthread_create and access it from the method it 
calls upon, but with print statements eventually was sure I had it working properly.

The final and still existing issue I encountered was not handling the merging properly with sub arrays being sorted 
but not being merged correctly. This was very agrivating because it would work with certain data sizes but not with large
ones which were required for the write up graph. I did however get it to work with up to three threads with these results
showing a slight speed up. 

This project really got the best of me, sorry for it not being completed entirely. 


[tuckerferguson@onyxnode79 multi-threaded]$ mergesort 1000000 1

Result: Sorting 1000000 elements took 0.71 seconds.

[tuckerferguson@onyxnode79 multi-threaded]$ mergesort 1000000 2

Sorting 1000000 elements took 0.69 seconds.



## Sources used

Instructor provided code, the C standard library (wikipedia),
Past Projects, Stackoverflow.com for referencing syntax, specifically struct,
and the man page for threads. 
