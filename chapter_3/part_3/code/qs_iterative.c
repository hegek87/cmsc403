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
	int *copy_left = malloc((mid-start)*sizeof(int));
	int *copy_right = malloc((end-mid)*sizeof(int));
	memcpy(copy_left, to_sort+start, (mid-start)*sizeof(int));
	memcpy(copy_right, to_sort+mid, (end-mid)*sizeof(int));
	int i,j,k;
	for(i = start, j = 0, k = 0; i < end; ++i){
		if(*(copy_left+j) < *(copy_right+k) && j < mid-start){
			*(to_sort+i) = *(copy_left+j++);
		}
		else{
			*(to_sort+i) = *(copy_right+k++);
		}
	}
	free(copy_left);
	free(copy_right);
}
	


void mergesort(int *to_sort, int start, int end){
	int half;
	if(start < end){
		half = start + ((end+start)/2);
		mergesort(to_sort, start, half);
		mergesort(to_sort, half, end);
	}
	
	merge(to_sort, start, half, end);
}


int main(void){
	int x[] = {1,5,2,4,10,24,5,2345,235,135,135,52,421,16,15};
	printArr(x,15);
	//partition(x,0,7);
	//printArr(x,7);
	quicksort(x, 0, 15);
	printArr(x,15);
	int y[] = {3,5,7,9,11,1,4,6,8,12};
	printArr(y, 10);
	merge(y, 0, 5, 10);
	printArr(y,10);
	return 0;
}
