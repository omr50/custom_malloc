#ifndef ALLOC_H
#define ALLOC_H

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdbool.h>

typedef struct {
	size_t size;
	struct Block* next;
	bool free;
} Block;


extern Block* block_list;
extern Block* end_of_list;


// creates a block and adds to end of linked list
Block* create_block(size_t size);

// using the memory address returned 
// to the user get the block pointer
Block* get_block_ptr(void* address);

// finds a free block with at least size bytes
Block* find_free_block(size_t size);

void* custom_malloc(size_t size);
void* custom_free(void* pointer);

// reallocates based on new size, can grow or de-size
// (block splitting functionality can be implemented later)
void* custom_realloc(void* address, size_t size);
// number of nelem = number of elements, elsize = size of each
void* custom_calloc(size_t nelem, size_t elsize);
// void* insert_block(size_t combined_size);

#endif
