#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

typedef struct {
	size_t size;
	Block* next;
	bool free;
} Block;


Block* block_list = nullptr;
Block* end_of_list = nullptr;


// creates a block and adds to end of linked list
Block* create_block(size_t size);

// using the memory address returned 
// to the user get the block pointer
Block* get_block_pointer(void* address);

// finds a free block with at least size bytes
Block* find_free_block(size_t size);

void* malloc(size_t size);
void* free(void* pointer);

// reallocates based on new size, can grow or de-size
// (block splitting functionality can be implemented later)
void* realloc(void* address, size_t size);
// number of nelem = number of elements, elsize = size of each
void* calloc(size_t nelem, size_t elsize);
// void* insert_block(size_t combined_size);

