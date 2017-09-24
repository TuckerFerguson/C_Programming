Author: Tucker Ferguson
Class: CS253-001

Overview:
This program takes in command line arguments which tell the machine to either print a usage message (-h)
or to search the text file for a matching value (-m <match>). On top of this it scans through the 
document to find the total number of words, lines, characters and digits (1-9).

Compiling and Using:
Enter the directory in which the main.c file is located. In this case it is p2, then execute the command
arguments stated above to be precise (./wc-match -m match <testfile) to scan the file for
matching words and to print the number of words, lines, characters and digits. For a usage message
use the flag -h. 

Testing:
I tested this code by starting it piece by piece as directions were introduced. I started with my flags
and made sure everything worked right without any errors (this was made easy due to getopt example).
Next I tested the word, line, character and digit counts by simply comparing my results to the examples
provided (data, data1). Next I tackled the matching method which simply was a trial by error. I would
write it then execute the file. Typically resulting in a segment fault error, then debug and try again.
There is most likely a better method than this but I am still pretty new to coding on a non-editor. 

Sources Used:
The tutoring lab, the textbook, in class tutors and help from the instructor and,
https://www.gnu.org/software/libc/manual/html_node/Using-Getopt.html#Using-Getopt

known Issues:
While getting my match working my wordcount sometimes varied from the proper results. 
Truth be told it still does for data however it is right for data1. I am also aware
that it is bad practice to have such a large block of print statements and hope to 
limit those as my C programming ability increases. 