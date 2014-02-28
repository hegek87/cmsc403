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


int main(void){
	int x[] = {10,9,8,7,6,5,4,3,2,1};
	printArr(x,10);
	mergesort(x,0, 9);
	printArr(x,10);
	return 0;
}
