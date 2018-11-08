# Project Number/Title {#mainpage}

* Author: Tucker Ferguson
* Class: CS453 [Operating Systems] Section 2


## Overview

This is a monitor version of the doubly linked list library implementation that we were provided.

## Manifest

INCLUDED FILES:

Entire Directory as requested

## Building the project

All project files should be in the same directory.

From the directory containing the .c source code, make the project:
    $ make

Run the project using exectuable:
    $ Usage: pc <poolsize> <#items/producer> <#producers>



## Features and usage

This program has taken a doubly linked list library implementation that we had been given and successfully made it into a monitor using wrappers. For testing purposes we were given a file named "pc.c" this simulates the producer consumer problem. 

## Testing

First I wrote code one method at a time. Which I then tried compiling after each addition. If errors occured I addressed them via reading the compiler and finetuning where the problems could be occuring. 

After I got a clean bill of health I used the testing script included with the project "test-pc.sh" as well as trying my own input several different ways with varying number of threads, items produced per producer, and the total number of producers. 


### Known Bugs

My only known bug at this moment is the program never actually exits. By the time I submit this it may be fixed but other than that it seems to be working. 


## Reflection and Self Assessment

This seemed like a very straight forward program with high level understanding required but when it came to actualy code it was not too heavy. 

## Sources used

Instructor provided code, the C standard library (wikipedia),
Past Projects, Stackoverflow.com for referencing syntax.
