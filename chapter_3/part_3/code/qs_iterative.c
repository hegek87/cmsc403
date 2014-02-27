#include "qs_iterative.h"
#include <stdio.h>

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

int main(void){
	int x[] = {1,5,2,4,10,24,5,2345,235,135,135,52,421,16,15};
	printArr(x,15);
	//partition(x,0,7);
	//printArr(x,7);
	quicksort(x, 0, 15);
	printArr(x,15);
	return 0;
}
