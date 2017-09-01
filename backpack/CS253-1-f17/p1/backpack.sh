#!/bin/bash
if [ "$1" = "" ];then
  echo "usage: $0 <output file>"
  echo "   output file - the file to save the grades in"
  exit 0;
fi
dest="$1"

#Generate the students assignment
make

#Make sure the program built
if [ ! -e "hello" ];then
  echo "P1: FAIL reason: Did not build the right executable" >> $dest
  exit 1 # fail the build
fi

#Make sure the clean target works
make clean
if [ "$?" != 0 ];then
        #We failed
        echo "P1: FAIL make clean" >> $dest
        exit 0
fi

#Make sure the run target builds and executes
output=$(make run)
if [ "$?" != 0 ];then
        #We failed
        echo "P1: FAIL make run" >> $dest
        exit 0
fi

# Check program output to make sure run actually executes program
if [[ ! $output =~ ^.*Invoking.*works.*$ ]];then
        #We failed
        echo "P1: FAIL make run does not execute program" >> $dest
        exit 0
fi

#Clean twice to make sure -f flag is used
make clean
make clean
echo "P1: PASS" >> $dest
