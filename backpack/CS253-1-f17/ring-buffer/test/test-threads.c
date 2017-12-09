
#include <pthread.h>
#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <ring.h>
pthread_mutex_t mutex;
int val;
  void * threadStart(void* data){
        int i; 
        pthread_t pid= pthread_self();
        printf("test-threads:main thread %ld\n", (long)pid);
        for(i = 0; i < val; i++){
        log_msg("Error: failed 1");                                                                                                                                                                           
        }  
        return NULL;      
    }
int main(int argc, char *argv[]){
    int i;
    if(argc != 3){
         printf("incorrect amount of command line args");
     }else{
    printf("test-threads:main thread %ld\n", (long) pthread_self());
    val = atoi(argv[2]);
    int threads = atoi(argv[1]);
    init_buffer();                                                                                     

   pthread_mutex_init(&mutex, NULL);  
   pthread_t pidArray[threads];
   for(i = 0; i < threads; i++){
   pthread_create(&pidArray[i], NULL, threadStart, NULL);
   pthread_join(pidArray[i], NULL);
     }
   printf("Threading is done c=\n" );
     }
     pthread_mutex_destroy(&mutex);
     return 0;

}
