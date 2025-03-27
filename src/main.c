#include <stdio.h>
// #include <stdlib.h> (this includes malloc)
#include <unistd.h>
#include <sys/mman.h>
#include "../headers/alloc.h"

int* create_array_range(int start, int end) {
	int num_elem = end - start;
	size_t size = num_elem * sizeof(int);
	int* array = custom_malloc(size);
	for (int i = 0; i < num_elem; i++) 
		array[i] = start + i;

	printf("Array Start: %p\n", array);
	printf("Array End: %p\n", array+num_elem);
	return array;
}

void print_array(int* array, int size) {
	for (int i = 0; i < 100;i++)
		printf("%d ", array[i]);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
}

int main() {

	printf("Blocksize: %d\n", sizeof(Block));
	int* array1 = create_array_range(0, 100);	
	int* array2 = create_array_range(100, 200);	

	print_array(array1, 100);
	print_array(array2, 100);
	// try to access next byte of array
	
	array2[110] = 5;
//	for (int i = 0; i < 100; i ++)
//		printf("%p ", array+i);
	printf("\n");

	printf("The program break is: %p\n", sbrk(0));
	printf("got to this point?\n");

	print_block_list();
}
