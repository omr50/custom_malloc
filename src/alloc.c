#include <stdio.h>
// #include <stdlib.h> (this includes malloc)
#include <unistd.h>
#include <sys/mman.h>
#include "../headers/alloc.h"



// check the size 
Block* create_block(size_t size) {
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
	}
	if (!block) {
		block = create_block(size);
	}


	
	
}
