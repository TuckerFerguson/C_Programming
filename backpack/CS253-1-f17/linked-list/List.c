#include <stdio.h>
#include <stdlib.h>
#include "List.h"


static struct node* reverse(struct node* L);
static void print(struct node* node);



struct list* createList()
{
	//java stuff 
	//List<Foo> List = new List<Foo>();
	struct list* list = (struct list*) malloc(sizeof(struct list));
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

int getSize(struct list* L)
{
	//java version
	//return this.size;
	return L->size;
}

Boolean isEmpty(struct list* L)
{
//	(L->size)? return TRUE: return 	FALSE;
	if (L->size == 0)
	return TRUE;
	else
	return FALSE;
}

void addAtFront(struct list* list, struct node* node)
{
	if (list == NULL) return;
	if (node == NULL) return;
	list->size++;
	node->next = list->head;
	node->prev = NULL;
	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	} else {
		list->head->prev = node;
		list->head = node;
	}
}

void addAtRear(struct list* list, struct node* node)
{
	if (list == NULL) return;
	if (node == NULL) return;
	list->size++;
	node->next = list->head;
	node->prev = NULL;
	//empty list no tacos 
	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	} else {
		list->head->next = node;
		list->head = node;
	}
}

struct node* removeFront(struct list* list)
{
	if (list == NULL){
	return NULL;
	}else if(list->tail == list->head){
		list->head = NULL;	
		list->tail = NULL;
	}
	else{
		list->head->next;
	}
	list->size--;


	return NULL;
}

struct node* removeRear(struct list* list){
	int i = 0;
	if (list == NULL){
		return NULL;
	}else if(list->tail == list->head){
	list->tail = NULL;
	list->head = NULL;
	}else{
		for(i = 0; i <= list-> size - 1; i++){
		  list->head->next;
		}
		list->tail;
	}
	list->size--;
	return NULL;
}

struct node* removeNode(struct list* list, struct node* node)
{
	if (node == list->head){
		return removeFront(list);
	}else if(node == list->tail){
		return removeRear(list);
	}else{
		struct node* current;
		current = list->head;

		struct node* temp;
		temp = current->next;
		while(temp != node){
			current = current->next;
			temp = temp->next;
		}
		current = temp->next;
		list->size--;
		return temp;
		}
	}

struct node* search(struct list* list, int key)
{
	//optional method (for learning)
	return NULL;
}

void reverseList(struct list* L)
{
	//also optional method
	L->tail = L->head;
	L->head  = reverse (L->head);
}

static struct node* reverse(struct node* L)
{	
	//optional
	return NULL;
}

void printList(struct list* L)
{
	if (L) print(L->head);
}

static void print(struct node* node)
{
	int count = 0;
	char *buf;

	while (node) {
		buf = toString(node->data);
		printf(" %s -->", buf);
		node = node->next;
		count++;
		if ((count % 6) == 0)
			printf("\n");
	}
	printf(" NULL \n");
}


void freeList(struct list* L)
{
	//required
}
