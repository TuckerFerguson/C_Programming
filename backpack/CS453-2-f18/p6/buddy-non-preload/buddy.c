
/**
 * Implementation of a memory allocator based on the Buddy System.
 * See Knuth Art of Computer Programming, vol. 1, page 442. 
 * Each available block starts with a header that consists
 * of a tag (free/reserved), kval (size of block 2^kval), next
 * and previous pointers. Each reserved block has the tag and kval 
 * field only. All allocations are done in powers of two. All requests
 * are rounded up to the next power of two.
 * 
 * @author Tucker Ferguson & Shane Panter
 * 
 */
 
#include "buddy.h"
int initialized = FALSE;

int next_Index(int k);
int next_Power(size_t a);
int power2(long int k);
/* the header for an available block */
struct block_header {
	short tag;
	short kval;
	struct block_header *next;
	struct block_header *prev;
};
const int RESERVED = 0;
const int FREE = 1;
const int UNUSED = -1;


/* supports memory upto 2^(MAX_KVAL-1) (or 64 GB) in size */
#define  MAX_KVAL  37

/* deafult memory allocation is 512MB */
const size_t DEFAULT_MAX_MEM_SIZE = 512*1024*1024;


/* A static structure stores the table of pointers to the lists in the buddy system.  */
struct pool {
	void *start; // pointer to the start of the memory pool
	int lgsize;  // log2 of size
	size_t size; // size of the pool, same as 2 ^ lgsize
	/* the table of pointers to the buddy system lists */
	struct block_header avail[MAX_KVAL];
} pool;

//This code was derived from the examples included in ~/examples/memory-magament as well as googling some syntax
int buddy_init(size_t size) { 
  int i;

    if(initialized){
        return TRUE;
    }

    if(size > DEFAULT_MAX_MEM_SIZE){
        errno = ENOMEM;
        return FALSE;
    }
    if(size == 0){
        pool.size = DEFAULT_MAX_MEM_SIZE;
        pool.start = sbrk(1L << pool.size);
        pool.start = sbrk(pool.size);
    }
    if(size < DEFAULT_MAX_MEM_SIZE && size >= 1){
        pool.size = DEFAULT_MAX_MEM_SIZE;
//make sure to change from int to long int        
        pool.start = sbrk(1L << pool.size);
        pool.start = sbrk(pool.size);
    } else {
        pool.lgsize = power2(size);
        pool.size = size;
//make sure to change from int to long int
        pool.start = sbrk(1L << pool.size);
    }
    if( errno == ENOMEM || pool.size < 0){
        perror("Could not allocate pool");
        exit(1);
    } 
    for(i = 0; i < MAX_KVAL; i++){
        pool.avail[i].next = &pool.avail[i];
        pool.avail[i].prev = &pool.avail[i];
        pool.avail[i].tag = UNUSED;
        pool.avail[i].kval = i;
    }

    struct block_header *ptr = (struct block_header *) pool.start;
    ptr->tag = FREE;
    ptr->kval = pool.lgsize;

    ptr->next = &pool.avail[ptr->kval];
    ptr->prev = &pool.avail[ptr->kval];

    pool.avail[ptr->kval].next = ptr->prev;
    pool.avail[ptr->kval].prev = ptr->next;

    pool.avail[pool.lgsize] = *ptr;
    initialized = TRUE;
    return TRUE;
}


void *buddy_malloc(size_t size)
{
//         if (argc != 2)
//         {
//                 fprintf(stderr, "Usage: %s <chunk size> \n", argv[0]);
//                 exit(1);
//         }
//         chunksize = atoi(argv[1]);

//         prev_endptr = sbrk(0); // argument of zero returns end of data segment

//         for (i = 0; i <1000; i++)
//         {
//                 ptr = (char *) malloc(sizeof(char)*chunksize);
//                 memset(ptr, 0, chunksize*sizeof(char));
//                 new_endptr = sbrk(0); // argument of zero returns end of data segment
//                 if (new_endptr != prev_endptr)
//                 {
//                         printf("iteration %d: end of data segment = %lx \n", i, (unsigned long)new_endptr);
//                         prev_endptr = new_endptr;
//                 }
//         }

     return NULL;

}


void *buddy_calloc(size_t nmemb, size_t size) 
{
	// unsigned int bytes_toAlloc;
    // buddy_init(size);
    // bytes_toAlloc = ((size+sizeof(block_header)-1)/sizeof(block_header))+ 1);
        return NULL;
}

void *buddy_realloc(void *ptr, size_t size) 
{   

// unsigned int bytes_toAlloc;
    // buddy_init(size);
    // bytes_toAlloc = ((size+sizeof(block_header)-1)/sizeof(block_header))+ 1);
        
	return NULL;
}


void buddy_free(void *ptr) 
{
}


void printBuddyLists()
{
      int i;
    for (i = 0; i < MAX_KVAL; i++) {
        printf("List %d: head: %p", i, &pool.avail[i]);
        if(pool.avail[i].tag == UNUSED){
            printf("--> <null>\n");
        } else {
            printf(" --> [tag=%d, kval=%d, addr=%p]\n", pool.avail[i].next->tag, pool.avail[i].next->kval, &pool.avail[i].next);
        }
    }
}

//Method for ensuring that the base address is a power of 2

int nextIndex(int size){
    int i =0;
    for(i = size; i <= MAX_KVAL; i++){
        if(pool.avail[i].tag != UNUSED){
            return i;
        }
    }
    return MAX_KVAL;
}
int nextPower(size_t size){

	int i=0;
    int j=0;
	while(i < DEFAULT_MAX_MEM_SIZE)
	{
		if(size < i){
			return j-1;
		}else{
			i = 1<<j;
			j++;
		}
	}
	return MAX_KVAL;
}

int power2(long int size) {
    unsigned int counter = 0;
    size--;

    while (size > 0) {
        size >>= 1;
        counter++;
    }

    return counter;
}

