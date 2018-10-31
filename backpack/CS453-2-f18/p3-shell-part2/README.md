# Project Number/Title {#mainpage}

* Author: Tucker Ferguson
* Class: CS453 [Operating Systems] Section 2

See CONTENTS.md for a description of the p1 starter files supplied to you in this folder. You
should complete the template below with your own words to finish this README file.

## Overview

This is a mini shell written in C. This shell has the ability to accept arguments
to commands and has some basic built-in commands such as exit and cd.

## Manifest

INCLUDED FILES:

 * Makefile
  * mydash.c
   * mydash.h
    * README - this file
     * valgrind.supp
      * pm.png

## Building the project

All project files should be in the same directory.

From the directory containing the .c source code, make the project:
    $ make

Run the project using exectuable:
    $ mydash

Navigate mydash as you'd expect to run bash:
 $ cd
 $ ls -r

## Features and usage

Dash's ability to take in command line arguments is handled heavily
with the readline() library. As well as some commands that required special
functionality such as "cd" and "-v". Each command can be accompanied by up to
2048 arguments.

These commands/arguments were implemented with the execvp call, which provides a
search for the command using PATH and executes the command. Several of the commands
required special tweaking in order to fit project requirements such as "cd", which has
configured to take in empty commands in which returns the user to home directory. This
is made possible with use of the environment variable HOME.

A similar concept was used for the prompt as well, except with a customized environment
variable "DASH_PROMPT". This time with the variable itself not existing on the predefined
environment variables, which allowed for customization of message upon new user.

Finally a show version "-v" method was implemented which returned the version of the project.
This version contains the git SHA code which is retrieved from git_version.c. Upon executing
version dash exits and user should be brought back to bash.

## Testing

Inititally I tested with nested print statements, as well as try to build the project
nearly every time I added or changed code. This allowed me to pinpoint areas that were
not working as expected due to warnings or errors.

I did all my editing in Visual Studio Code which also allowed me to see errors in
syntax, but due to my methodology of compiling nearly every change this rarely
occured.

As I developed each section of the project (see pm.png) one at a time often. I tested
inputs, and commands. Often with the result of segfault or inproper output. This allowed
me to not work further ahead of already prexhisting issues and kept the sanity.

Upon making sure that all specifications of the project appeared to be working properly. I
ran the smoketest-files included which allowed me to fine tune any existing major errors. I also
added a few tests which are documented in the file "mydashTests" ontop of that I checked many commands/argument combinations simply
to see if readline had them included or not and if mydash could handle them.

### Valgrind

I used valgrind as described in project write up.

### Known Bugs

I appear to have some memory leakage to valgrind even after supression file was updated. As well as issues with
multiple white space user enteries.


## Reflection and Self Assessment

Many of my testing methods and errors I often encountered are listed in the testing section but I will
go into more detail. I often had segfaults usually due to not handling memory properly or over populating
defined data structures. Ontop of that I ran into issues with type conversions a few times and honestly
had difficulty spreading my program around and not making its bulk in main.

The hardest issues I encountered were some of the new concepts we were asked to use. Such as implementing the
environment variables. Also readline was relatively new to me so fully understanding it was not easy at first.
Even figuring out how to edit the supression file took quite a bit of reading.

## Sources used

Instructor provided code, the C standard library (wikipedia),
Past Projects, Stackoverflow.com for referencing syntax.
