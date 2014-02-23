#include <stdio.h>

// 3.1 (a)
double power(double a, int b){
	if(b <= 0){ return 1; }
	else{ return a * power(a,b-1); }
}

// 3.1 (b)
double power_tail(double a, int b, double so_far){
	if(b <= 0){ return so_far; }
	else{ return power_tail(a,b-1,so_far*a); }
}

// 3.2 
int readMax(int cur){
	int max = cur, x;
	scanf("%d", &x);
	if(x != 0){
		if(x > max){ return readMax(x); }
		else{ return readMax(max); }
	}
	else{ return max; }
}
		
		

int main(void){
	printf("%f\n", power(5,3));
	printf("%f\n", power_tail(5,3,1));
	printf("%d\n", readMax(0));
}
