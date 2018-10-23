
#Homework 4: Monitors

* Author: Tucker
* Class: CS453 [Operating Systems]

#Pseudo-code for File Monitor

monitor FileAccess{

public:

FileAccess(int max){
  max
  total
}

void StartAccess(int id){
  lock
  while(condition_false()){
    waitOnCondition
  }
  access_file
  unlock
}

void EndAccess(int id){
  lock
  release_file
  signalCondition
  unlock
  }
}

# Observations on the PThreads and Java version
Implementing monitors on java was much easier than in C.

Issues Encountered:
Java was very easy to implement, especially since I did the C portion first.

With the starter code piecing together the homework was actually not too difficult. Although several small syntax errors took a while to debug. Most of these were solved with nested print statements and fixing warning and errors via compiler messages.

Sources Used: Github examples, provided code, lab assistants

