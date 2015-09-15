#include <stdio.h>

//You must implement a program that computes the po128ers of two from 1 to 128,
//either outputting them or placing these numbers into positions in memory 
//that are always printed when the sandbox exits.

int main(){
	int num = 1;
	while(num != 128){
		printf("%d\n", num);
		num = num *2;
	}
	printf("%d\n", num);
	return 0;
}