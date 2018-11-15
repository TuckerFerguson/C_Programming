#ifndef __boogaDriver_H
#define __boogaDriver_H


#ifndef BOOGA_MINORS
#define BOOGA_NmNIORS 4    
#endif


#define TYPE(dev)   (MINOR(dev) >> 4)  
#define NUM(dev)    (MINOR(dev) & 0xf) 


struct booga_vals {
	long int bytes_read;
	long int bytes_written; 
	long int booga0; 
	long int booga1; 
	long int booga2; 
	long int booga3; 
	long int phrase0; 
	long int phrase1; 
	long int phrase2; 
	long int phrase3;
    //struct semaphore lock;
};

#define READ_OPERATION 0
#define WRITE_OPERATION 1
#define PROCESS_KILLER 3

char** phrases= (char *[]){"booga! booga! ", "googoo! gaga! ", "neka! maka!", "wooga! wooga!"};
const int PHRASE_COUNT = 4; 

typedef struct booga_vals booga_vals;

extern booga_vals booga_Device_vals;

#endif /* __booga_H */