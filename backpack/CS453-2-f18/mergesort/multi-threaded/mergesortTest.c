/*
*
* @Authors Shane Panter, Tucker Ferguson
* October 3, 2018
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
int part = 0;
typedef struct mergeThreads mergeThreads;
struct mergeThreads{
	int n;
	int thread_count;
	pthread_mutex_t mutex;
	int *Array;
};
struct mergeThreads *myMerger;

// function prototypes
int check_if_sorted(int A[], int n);
void generate_random_array(int A[], int n, int seed);
void serial_mergesort(int A[], int p, int r); 
void* parrallel_mergesort(void* arg);
void merge(int A[], int p, int q, int r);
void insertion_sort(int A[], int p, int r);
double getMilliSeconds();


/*
 * generate_random_array(int A[], int n, int seed):
 *
 * description: Generate random integers in the range [0,RANGE]
 *              and store in A[1..n]
 */

#define RANGE 1000000

void generate_random_array(int A[], int n, int seed)
{
    int i;

	srandom(seed);
    for (i=1; i<=n; i++)
        A[i] = random()%RANGE;
}


/*
 * check_if_sorted(int A[], int n):
 *
 * description: returns TRUE if A[1..n] are sorted in nondecreasing order
 *              otherwise returns FALSE
 */     

int check_if_sorted(int A[], int n) 
{
	int i=0;

	for (i=1; i<n; i++) {
		//printf("\n %d < %d\n",A[i],A[i+1]);
		if (A[i] > A[i+1]) {
			return FALSE;
		}
	}
	return TRUE;
}

/*
*
*My attempt at handling threading for parrallel merge sort, I access the variables here just fine 
*and the sorting works for up to two threads but once I introduce third or higher it gets bad results
*
*/
void* parrallel_mergesort(void* arg) 
{	
	struct mergeThreads *Merger = (struct mergeThreads*)arg;
	int test =Merger->n;
	int *subArray=Merger->Array;
	int thread_count=Merger->thread_count;
	pthread_mutex_lock(&(Merger->mutex));
	int thread_part = part++;
	// printf("threadpart: %d. #elements: %d. threadCount: %d",thread_part,test,thread_count);
	int low = thread_part * (test/thread_count)+1;
	int high = (thread_part + 1) * (test/thread_count);
	// printf("low: %d\n",low);
	// printf("high: %d\n",high);
	if (low < high){
		serial_mergesort(subArray,low,high);
	}
	pthread_mutex_unlock(&(Merger->mutex));
	pthread_exit(NULL);
}

int main(int argc, char **argv) {
	
	if (argc < 3) { // there must be at least one command-line argument
			fprintf(stderr, "Usage: %s <input size> <number of threads> [<seed>] \n", argv[0]);
			exit(1);
	}
	
	int n = atoi(argv[1]);
	int seed = 1;
	int threadCount;
	int i = 0;
	if (argc == 4)
	seed = atoi(argv[3]);
	threadCount = atoi(argv[2]);
	
	int *A = (int *) malloc(sizeof(int) * (n+1)); // n+1 since we are using A[1]..A[n]
	myMerger = malloc(sizeof(struct mergeThreads));

	// generate random input
	generate_random_array(A,n, seed);
	myMerger->Array = A;
	myMerger->n =n;
	myMerger->thread_count = threadCount;
	
	//initialize threads
	pthread_t *threads;
	double start_time;
	double sorting_time;
    threads = (pthread_t *) malloc(sizeof(pthread_t)*threadCount);
	//creating amount of threads specified by user
	start_time = getMilliSeconds();

	for(i = 0; i < threadCount; i++){
		pthread_create(&threads[i], NULL, parrallel_mergesort, (void*)myMerger);
	}
	for(i = 0; i < threadCount; i++){
		pthread_join(threads[i], NULL);
	}
	merge(A,1,(n+1)/2,n);
	for(i=0;i<=n;i++){
	//printf(" %i ",A[i]);
	}
	
	sorting_time = getMilliSeconds() - start_time;
	
	// print results if correctly sorted otherwise cry foul and exit
	if (check_if_sorted(A,n)) {
		printf("Sorting %d elements took %4.2lf seconds.\n", n,  sorting_time/1000.0);
	} else { 
		printf("%s: sorting failed!!!!\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS); 
} 
