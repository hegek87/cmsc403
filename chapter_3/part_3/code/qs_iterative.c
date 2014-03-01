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

void destroy_node(struct Node *to_die){
	//free(to_die->x);
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
		int *x = malloc(sizeof(int));
		stack_pop(st, x);
		free(x);
	}
	free(st);
}

int stack_pop(struct Stack *st, int *val){
	if(stack_empty(*st)){
		return -1;
	}
	st->size--;
	struct Node *top = st->top;
	st->top = st->top->next;
	*val = *top->x;
	destroy_node(top);
	return 1;
}

void stack_push(struct Stack *st, int val){
	struct Node *new_top = create_node(&val);
	if(!stack_empty(*st)){
		new_top->next = st->top;
		st->top->next = new_top;
		st->size++;
		return;
	}
	st->top = new_top;
	st->size++;
}
	
int stack_empty(struct Stack st){ return !st.size; }


int main(void){
	struct Stack *test = create_stack();
	int a,y,z;
	stack_push(test,10);
	stack_push(test,11);
	stack_push(test,12);
	stack_pop(test,&a);
	stack_pop(test,&y);
	printf("A: %d\tY: %d\n", a,y);
	//stack_pop(test,&z);
	//destroy_stack(test);
	int x[] = {10,9,8,7,6,5,4,3,2,1};
	printArr(x,10);
	mergesort(x,0, 9);
	printArr(x,10);
	return 0;
}
