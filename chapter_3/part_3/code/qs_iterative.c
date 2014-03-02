#include "qs_iterative.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

void quicksort(int to_sort[], int begin, int end){
	if(begin >= end){ return; }
	int part = partition(to_sort, begin, end);
	quicksort(to_sort, begin, part);
	quicksort(to_sort, part+1, end);
	return;
}

int partition(int to_sort[], int begin, int end){
	int p = begin-1, i = begin;
	for(i = begin; i < end; ++i){
		if(to_sort[i] > to_sort[end-1]){
			continue;
		}
		else{
			swap(&to_sort[i], &to_sort[++p]);
		}
	}
	return p;
}

void printArr(int *x, int len){
	int i = 0;
	while(i++ < len){
		printf("%d ", *x++);
	}
	printf("\n");
}


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
	


void mergesort(int *to_sort, int start, int end){
	if(start < end){
		int half = (start+end)/2;
		mergesort(to_sort, start, half);
		mergesort(to_sort, half+1, end);
		merge(to_sort, start, half, end);
	}
}

void stack_mergesort(int *to_sort, int len){
	int half = len / 2, cur = 1, i;
	struct Stack *st = create_stack();
	for(i = 0; i < len; ++i){
		stack_push(st, to_sort+i);
	}
	while(cur < half){
		while(!stack_empty(*st)){
			i = 0;
			
			// Get first cur elements
			int front[cur], back[cur];
			while(!stack_empty(*st) && 
			

void destroy_node(struct Node *to_die){
	free(to_die);
}

struct Node *create_node(int *val){
	struct Node *ret = create_empty_node();
	ret->x = val;
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
	struct Stack *test = create_stack();
	//int a,y,z;
	int y = 10, b = 6, c = 100;
	stack_push(test,&y);
	stack_push(test,&b);
	stack_push(test,&c);
	while(!stack_empty(*test)){
		printf("NEXT: %d\n", *stack_pop(test));
	}
	destroy_stack(test);
	int x[] = {10,9,8,7,6,5,4,3,2,1};
	printArr(x,10);
	mergesort(x,0, 9);
	printArr(x,10);
	return 0;
}
