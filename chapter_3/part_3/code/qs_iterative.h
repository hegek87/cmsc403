#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <stddef.h>
void quicksort(int *, int,int);
int partition(int *,int,int);
void swap(int *,int *);
void printArr(int *m, int);

void mergesort(int *, int,int);
void merge(int *, int, int, int);

struct Node{
	int *x;
	struct Node *next;
};

struct Stack{
	struct Node *top;
	size_t size;
};

void destroy_node(struct Node *);
struct Node *create_node(int*);
struct Node *create_empty_node();

struct Stack *create_stack();
void destroy_stack(struct Stack *);
int *stack_pop(struct Stack *);
void stack_push(struct Stack *, int *);
int stack_empty(struct Stack);

void stack_mergesort(int *,int);
#endif
