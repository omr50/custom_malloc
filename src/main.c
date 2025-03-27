#include <stdio.h>
// #include <stdlib.h> (this includes malloc)
#include <unistd.h>
#include <sys/mman.h>
#include "../headers/alloc.h"

int main() {

	int* array = NULL;
	array = custom_malloc(100 * sizeof(int));

	for (int i = 0; i < 100; i ++)
		array[i] = i+1;

	for (int i = 0; i < 100; i ++)
		printf("%d ", array[i]);
	printf("\n");
}
