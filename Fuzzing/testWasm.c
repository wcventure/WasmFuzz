#include <stdio.h>
#include <stdlib.h>

int func(int x)
{
	int sum=0;
	for (int i=0;i<x;i++)
		sum = x*(x+x);
	return sum;
}

int main(int argc, char ** argv) 
{
	printf("%d->WebAssembly loaded.\n", func(10));
	return 0;
}