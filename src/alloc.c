#include <stdio.h>
// #include <stdlib.h> (this includes malloc)
#include <unistd.h>
#include <sys/mman.h>
#include "../headers/alloc.h"



// check the size 
Block* create_block(size_t size) {
	Block* block;
	// is it not thread safe because
	// by the time we allocate, the 
	// program break could have moved due
	// to another function in another thread
	// requesting memory?
	if (size <= 0)
		return null;
	Block* block = sbrk(0);
	void* data = sbrk(size + sizeof(Block));	
	if (data == (void*)-1) 
		return NULL; // sbrk failed
			     //
	// add block to the back of the list
	
	// fill out block fields
	block.size = size;
	block.free = true;
	block.next = nullptr;

	if (!block_list){
		block_list = block;
		end_of_list = block;
	} else {
		end_of_list.next = block;
		end_of_list = end_of_list.next;
	}
	return block;
}

Block* get_block_pointer(void* address) {
	return (Block*)address -1;
}

Block* find_free_block(size_t size) {
	// loop through list, find block
	// return null or valid block 
	Block* ptr = block_list;
	while (ptr && !(ptr->free & ptr->size >= size)) {
		ptr = ptr->next;	
	}

	return ptr;
}

void malloc(size_t size) {

	if (size <= 0) {
		return NULL;
	}
	
	Block* block = nullptr;

	if (block_list) {
		block_list = find_free_block(size);
		if (!block) {
			return NULL;
		}
	} else {
		block = create_block(size);
		if (!block) {
			// can't allocate memory
			return NULL;
		}
	}

	// at this point we should have memory
	block->free = false;
	// increment pointer to skip metadata
	return block+1;
}

void* free(void* address) {
	if (!address) {
		return;
	}
	Block* block = get_block_pointer(address);
	block->free = true;
}

void* realloc(void* pointer, size_t size) {
	if (!pointer) {
		return malloc(size);
	}
	Block* block = get_block_ptr(pointer);
	if (block->size >= size)
		return pointer;

	void* new_ptr = malloc(size);
	if (!new_ptr) {
		return NULL;
	}
	memcpy(new_ptr, ptr, block->size);
	free(pointer);
	return new_ptr;
}

void* calloc(size_t nelem, size_t elsize) {
	void* pointer = malloc(nelem * elsize);	
	memset(pointer, 0, size);
	return pointer;
}
