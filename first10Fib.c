#include <stdio.h>


//You must provide a program computing the first ten fibonacci numbers.
//The resulting program should output these numbers or place them in the
//first ten memory locations when exiting.

void fib(int n){
	int array[n]; 
	array[0] = 0;
	array[1] = 1;
	for(int i = 2; i < n; ++i){
		array[i] = array[i - 1] + array[i - 2];
	}
	for(int i = 0; i < n; ++i){
		printf("%d\n", array[i]);
	}
}


int main(){
	fib(10);
	return 0;
}
