/*
=============================================================================

CS 50300 Operating Systems Lab1 - Alligned Memory Allocator

Block_Memory.h Source code		

Kartik Sooji (ksooji)

=============================================================================
*/



/*
The block_pool data structure is used to store the infomation regarding
the large chunk of memory created as the user requests
*/
struct	block_pool
{
	struct	dll_block* pool_head;				
	int total_num_blocks;	
	int alignment_bytes;	
	int num_avail_blocks;
}*pool;



/*
The dll_block data structure is used to store the infomation regarding
each block in the memory pool which is a DLL that keeps the information about the next
and previous memory blocks
*/

struct dll_block	
{
	struct dll_block* prev;
	void* data_ptr;
	struct dll_block* next;
};	


/*Creates a large amount of the memory as requested and 
divide the memory pool into smaller blocks that are alligned accordingly
*/
struct block_pool* create_block_pool(int num_blocks,int block_size,int alignment);

//Allocate the alligned blocks that are created by the create function on request
void* alloc_align_block(struct block_pool* pool);

//Dellocate the assigned blocks that are assinged by the assign function on request
void free_align_block(struct block_pool* pool, void* blk);

