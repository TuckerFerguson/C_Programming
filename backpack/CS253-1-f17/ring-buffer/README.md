Project Ring buffer (P6) 
Author: Tucker Ferguson
Class: CS253 Section 1

Overview: 
This program is a ring buffer that prints out the last 5 log messages in order from oldest to newest.

Compiling and Using: 
To run the test programs you will need to set the paths to find the library:

```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
```

Then run the test programs as follows:

```
./grader
```

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

Sources used:
I took advantage of the CS resources. As well as code provided to us by Shane. I also used an example
from google on how to properly print to files. 


