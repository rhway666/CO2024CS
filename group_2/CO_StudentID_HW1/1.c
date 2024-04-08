#include <stdio.h>
int main(){
	int a, b;
	FILE *input = fopen("../input/1.txt", "r");
	fscanf(input, "%d %d", &a, &b);
	fclose(input);
	//a = a * b;
	asm volatile("mul %0, %1, %2"
				 : "=r" (a)
				 : "r" (a), "r" (b)
				);
	printf("%d\n", a);
	return 0;
}


