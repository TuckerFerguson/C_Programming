Project Ring buffer (P6) 
Author: Tucker Ferguson
Class: CS253 Section 1

Overview: 
-This program is a ring buffer that prints out the last 5 log messages in order from oldest to newest.

-Second part implements threads to handle dumping to log file.

Compiling and Using: 
To run the test programs you will need to set the paths to find the library:

```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
```

Then run the test programs as follows:

```
./grader        (For part two you must pass in two arguments as well)
```              -Amount of threads, and total iterations. 

Or the run.sh script will set the path for you and execute valgrind:

```
./run.sh
```

To run the autograder before submitting, run:

```
./backpack.sh
```

Testing: 
First I made sure that the print statement was actually being printed to a file.
Next I made sure that the test file printed approprately from oldest to newest. After that I began 
checking base cases. Such as logging a NULL string or a string that is too long.

Part 2: I made sure that outputs matched what I expected. I messed around with
log length and made sure that the dump file was printed properly. Next I made sure
that the threads were changing in value by printing out their ID often in loops. 
Figuring out how to create and join a user specified amount of threads was a debugging
nightmare. However, with the help of tutors I found an easy way of managing this with
a pid array. 



Sources used:
I took advantage of the CS resources. As well as code provided to us by Shane. I also used an example
from google on how to properly print to files. 


