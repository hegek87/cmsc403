#include "qs_iterative.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}
	
// (3.3) Quicksort
void quicksort(int to_sort[], int begin, int end){
	if(begin < end){
		int part = partition(to_sort, begin, end);
		quicksort(to_sort, begin, part-1);
		quicksort(to_sort, part+1, end);
	}
}

int partition(int to_sort[], int begin, int end){
	int p = begin-1, i;
	for(i = begin; i < end; ++i){
		if(to_sort[i] <= to_sort[end]){
			swap(&to_sort[i], &to_sort[++p]);
		}
	}
	swap(&to_sort[p+1],&to_sort[end]);
	return p+1;
}

void printArr(int *x, int len){
	int i = 0;
	while(i++ < len){
		printf("%d ", *x++);
	}
	printf("\n");
}

int min(int x, int y){ return (x<y) ? x : y; }

void merge(int *to_sort, int start, int mid, int end){
	int l_len = mid-start+1, r_len = end-mid;
	
	int left_copy[l_len], right_copy[r_len];
	int i;
	for(i = 0; i < l_len; ++i){
		left_copy[i] = *(to_sort+start+i);
	}
	for(i = 0; i < r_len; ++i){
		right_copy[i] = *(to_sort+mid+i+1);
	}
	
	int j,k;
	for(i = 0, j = 0, k = start; k <= end; ++k){
		if(j >= r_len){
			*(to_sort+k) = left_copy[i++];
		}
		else if(i >= l_len){
			*(to_sort+k) = right_copy[j++];
		}
		else if(left_copy[i] < right_copy[j]){
			*(to_sort+k) = left_copy[i++];
		}
		else{
			*(to_sort+k) = right_copy[j++];
		}
	}
}

// (3.3) Mergesort
void mergesort(int *to_sort, int start, int end){
	if(start < end){
		int half = (start+end)/2;
		mergesort(to_sort, start, half);
		mergesort(to_sort, half+1, end);
		merge(to_sort, start, half, end);
	}
}

// (3.4 a) Stack based quicksort
void stack_quicksort(int *to_sort, int len){
	int start = 0, end = len-1;
	struct Stack *st = create_stack();
	stack_push(st, &start);
	stack_push(st, &end);
	while(!stack_empty(*st)){
		// Get top and bottom elements
		end = *stack_pop(st);
		start = *stack_pop(st);
		
		// Find partition
		int part = partition(to_sort, start, end);
		
		// We aren't done, push top and bottom of left side
		if(part - 1 > start){
			int p = part-1;
			stack_push(st, &start);
			stack_push(st, &p);
		}
		// We aren't done, push top and bottom of right side
		if(part+1 < end){
			int p = part+1;
			stack_push(st, &p);
			stack_push(st, &end);
		}
	}	
}

// (3.4 b) Stack based Mergesort
void stack_mergesort(int *to_sort, int len){
	int SORTED = 1;
	int UNSORTED = 0;
	int start = 0, end = len-1, ready;
	struct Stack *st = create_stack();
	// Prepare stack
	stack_push(st, &start);
	stack_push(st, &end);
	stack_push(st, &UNSORTED);
	while(!stack_empty(*st)){
		ready = *stack_pop(st);
		end = *stack_pop(st);
		start = *stack_pop(st);
		int mid = (start+end)/2;
		// If the sublists are sorted, merge them
		if(ready){
			merge(to_sort,start,mid,end);
		}
		else{
			if(start < end){
				/*
				* By the time we get start,end back, the sublists
				* will be sorted.
				*/
				stack_push(st,&start);
				stack_push(st,&end);
				stack_push(st,&SORTED);
				
				stack_push(st,&start);
				stack_push(st,&mid);
				stack_push(st,&UNSORTED);
				
				int p = mid+1;
				stack_push(st,&p);
				stack_push(st,&end);
				stack_push(st,&UNSORTED);
			}
		}
	}
}

void destroy_node(struct Node *to_die){
	free(to_die);
}

struct Node *create_node(int *val){
	struct Node *ret = create_empty_node();
	ret->x = malloc(sizeof(int));
	memcpy(ret->x, val,sizeof(int));
	return ret;
}

struct Node *create_empty_node(){
	return malloc(sizeof(struct Node));
}

struct Stack *create_stack(){
	struct Stack *st = malloc(sizeof(struct Stack));
	st->size = 0;
	st->top = NULL;
	return st;
}
	
	
void destroy_stack(struct Stack *st){
	while(!stack_empty(*st)){
		free(stack_pop(st));
	}
	free(st);
}

int *stack_pop(struct Stack *st){
	if(stack_empty(*st)){
		return NULL;
	}
	st->size--;
	struct Node *top = st->top;
	int *val = top->x;
	st->top = st->top->next;
	destroy_node(top);
	//printf("VAL BEING POPPED: %d\n", *val);
	return val;
}

void stack_push(struct Stack *st, int *val){
	struct Node *new_top = create_node(val);
	if(!stack_empty(*st)){
		new_top->next = st->top;
		st->top = new_top;
		st->size++;
		return;
	}
	st->top = new_top;
	st->size++;
}
	
int stack_empty(struct Stack st){ return !st.size; }


int main(void){

	printf("STACK BASED MERGESORT\n");
	int z[] = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
	printArr(z,20);
	stack_mergesort(z,20);
	printArr(z,20);
	
	printf("STACK BASED QUICKSORT\n");
	int x[] = {18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
	printArr(x,18);
	stack_quicksort(x,18);
	printArr(x,18);
	
	printf("REGULAR QUICKSORT\n");
	int y[] = {13,12,11,10,9,8,7,6,5,4,3,2,1};
	printArr(y,13);
	quicksort(y,0,12);
	printArr(y,13);
	
	printf("REGULAR MERGESORT\n");
	int m[] = {12,11,10,9,8,7,6,5,4,3,2,1};
	printArr(m,12);
	mergesort(m,0,11);
	printArr(m,12);

	return 0;
}
