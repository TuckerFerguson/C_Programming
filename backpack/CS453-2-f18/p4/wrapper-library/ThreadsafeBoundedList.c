//
//@Author: Tucker Ferguson
//@Date: November 7, 2018
//
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <Node.h>
#include "ThreadsafeBoundedList.h"


//provided struct
struct tsb_list
{
    struct list *list;
    int capacity;
    Boolean stop_requested;
    pthread_mutex_t mutex;
    pthread_cond_t listNotFull;
    pthread_cond_t listNotEmpty;
};

/**
 * This wrapper method creates an empty list 
 */
struct tsb_list *tsb_createList(int (*equals)(const void *, const void *),
                                char *(*toString)(const void *),
                                void (*freeObject)(void *),
                                int capacity)
{
    struct tsb_list *tsb_list = malloc(sizeof(struct tsb_list));
    tsb_list->list = createList(equals, toString, freeObject);
    tsb_list->capacity = capacity;
    tsb_list->stop_requested = FALSE;
    pthread_mutex_init(&tsb_list->mutex, NULL);
    pthread_cond_init(&tsb_list->listNotFull, NULL);
    pthread_cond_init(&tsb_list->listNotEmpty, NULL);
    return tsb_list;
}
/**
 * This wrapper method is the deconstructor
 */
void tsb_freeList(struct tsb_list *list)
{
    pthread_mutex_lock(&(list->mutex));
    freeList(list->list);
    pthread_mutex_unlock(&(list->mutex));
}

/**
 * This wrapper method returns the size of the List
 */
int tsb_getSize(struct tsb_list *list)
{
    pthread_mutex_lock(&(list->mutex));
    int size = getSize(list->list);
    pthread_mutex_unlock(&(list->mutex));
    return size;
}

/**
 * This wrapper method returns the capacity of the List
 */
int tsb_getCapacity(struct tsb_list *list)
{
    pthread_mutex_lock(&(list->mutex));
    int capacity = list->capacity;
    pthread_mutex_unlock(&(list->mutex));
    return capacity;
}
/**
 * This wrapper method sets the capacity of the List
 */
void tsb_setCapacity(struct tsb_list *list, int capacity)
{
    pthread_mutex_lock(&(list->mutex));
    list->capacity = capacity;
    pthread_mutex_unlock(&(list->mutex));
}

/**
 * This wrapper method returns whether the List is empty
 */
Boolean tsb_isEmpty(struct tsb_list *list)
{
    pthread_mutex_lock(&(list->mutex));
    Boolean is_empty = isEmpty(list->list);
    pthread_mutex_unlock(&(list->mutex));
    return is_empty;
}

/**
 * This wrapper method returns whether the List is full
 */
Boolean tsb_isFull(struct tsb_list *list)
{
    pthread_mutex_lock(&(list->mutex));
    Boolean is_full;
    if ((getSize(list->list)) == list->capacity)
    {
        is_full = TRUE;
    }
    else
    {
        is_full = FALSE;
    }
    pthread_mutex_unlock(&(list->mutex));
    return is_full;
}

/**
 * This wrapper method adds to front of the list
 */
void tsb_addAtFront(struct tsb_list *list, NodePtr node)
{
    pthread_mutex_lock(&(list->mutex));
    while (getSize(list->list) + 1 > list->capacity)
        pthread_cond_wait(&(list->listNotFull), &(list->mutex));
    addAtFront(list->list, node);
    pthread_mutex_unlock(&(list->mutex));
}

/**
 * This wrapper method adds to back of the list
 */
void tsb_addAtRear(struct tsb_list *list, NodePtr node)
{
    pthread_mutex_lock(&(list->mutex));
    while (getSize(list->list) + 1 > list->capacity)
        pthread_cond_wait(&(list->listNotFull), &(list->mutex));
    addAtRear(list->list, node);
    pthread_mutex_unlock(&(list->mutex));
}

/**
 * This wrapper method removes from the front of the list
 */
NodePtr tsb_removeFront(struct tsb_list *list)
{
    pthread_mutex_lock(&(list->mutex));
    NodePtr removed_node = removeFront(list->list);
    pthread_cond_signal(&(list->listNotEmpty));
    pthread_mutex_unlock(&(list->mutex));
    return removed_node;
}

/**
 * This wrapper method removes from the back of the list
 */
NodePtr tsb_removeRear(struct tsb_list *list)
{
    pthread_mutex_lock(&(list->mutex));
    NodePtr removed_node = removeRear(list->list);
    pthread_cond_signal(&(list->listNotEmpty));
    pthread_mutex_unlock(&(list->mutex));
    return removed_node;
}
/**
 * This wrapper method removes a node from the list
 */
NodePtr tsb_removeNode(struct tsb_list *list, NodePtr node)
{
    pthread_mutex_lock(&(list->mutex));
    NodePtr removed_node = removeNode(list->list, node);
    pthread_mutex_unlock(&(list->mutex));
    return removed_node;
}
/**
 * This wrapper method searches the list for an object
 */
NodePtr tsb_search(struct tsb_list *list, const void *obj)
{
    pthread_mutex_lock(&(list->mutex));
    NodePtr found = search(list->list, obj);
    pthread_mutex_unlock(&(list->mutex));
    return found;
}
/**
 * This wrapper method reverses the list
 */
void tsb_reverseList(struct tsb_list *list)
{
    pthread_mutex_lock(&(list->mutex));
    reverseList(list->list);
    pthread_mutex_unlock(&(list->mutex));
}
/**
 * This wrapper method prints the list
 */
void tsb_printList(struct tsb_list *list)
{
    pthread_mutex_lock(&(list->mutex));
    printList(list->list);
    pthread_mutex_unlock(&(list->mutex));
}

void tsb_finishUp(struct tsb_list *list)
{
    pthread_cond_broadcast(&(list->listNotEmpty));
    //pthread_cond_broadcast(&(list->listNotFull));
}