/*
=============================================================================

CS 50300 Operating Systems Lab1 - Alligned Memory Allocator

Alloc.c Source code		

Kartik Sooji (ksooji)

=============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include"block_memory.h"

/*
create_block_pool method creates a pool of memory that users requested for and returns the initial address
of the memory pool as the a pointer to the pool head which is a DLL that stores the address of the next block
*/

struct block_pool* create_block_pool(int num_blocks,int block_size,int alignment)
{
	int i=0;
	struct dll_block *dll_head, *new_blk, *cur;
	void* free_memory;
	
	printf("==============================================================\n");
	printf("CSCI 50300 Operating Systems Lab1 - Alligned Memory Allocator\n");
	printf("Alloc.c Source code and block_memory.h header file\n");
	printf("Kartik Sooji (ksooji)\n");
	printf("==============================================================\n");

	if(num_blocks <= 0){		
		printf("--------- Input Error : Invalid Input for Number of Blocks ---------\n");
		return 0;	
	}

	if(block_size <= 0){		
		printf("--------- Input Error : Invalid Input for Block Size ---------\n");	
		return 0;	
	}

	if(alignment <= 0){		
		printf("--------- Input Error : Invalid Input for Allignment bytes for each block ---------\n");	
		return 0;	
	}

	//Memory allocation to for one node to store the information of the memory pool	
	pool = (struct block_pool*)malloc(sizeof(struct block_pool));
	if(pool == NULL){
		printf("--------- Malloc() Error : Block Pool Creation ---------\n");	
		return 0;
	}

	//Assigning the user formal parameters to struct for the internal use among the functions 
	pool->pool_head = NULL;
	pool->total_num_blocks = num_blocks;
	pool->alignment_bytes = alignment;
	pool->num_avail_blocks = 0;



	//Memory allocation to for user requested chunk of memory for the pool	
	free_memory = (void*)malloc(((int)(block_size/alignment)+1)*(num_blocks+1));
	if(free_memory == NULL){
		printf("--------- Malloc() Error : Free Memory Creation ---------\n");	
		return 0;
	}
//	printf("-----------%ld",(unsigned long)free_memory);


/*	//Memory allocation to for head node of the block DLL
	dll_head = (struct dll_block*)malloc(sizeof(struct dll_block));
	if( dll_head == NULL){
		printf("--------- Malloc() Error : DLL Head Creation ---------\n");	
		return 0;
	}
	dll_head->prev = NULL;
	dll_head->data_ptr = free_memory;
//	dll_head->data_ptr = free_memory + block_size + alignment - ((int)(cur->data_ptr + block_size) % pool->alignment_bytes);
//	dll_head->data_ptr =(void *) ( (char*)free_memory + alignment - ((int)(cur->data_ptr + block_size) % pool->alignment_bytes) );			
	dll_head->next = NULL;
// */
	//Memory allocation to for head node of the memory pool	
	pool->pool_head = (struct dll_block*)malloc(sizeof(struct dll_block));
	if( pool->pool_head == NULL){
		printf("--------- Malloc() Error : Pool Head Creation ---------\n");	
		return 0;
	}


	//printf("--------- Block Pool Head Created ---------\n", i);
//	(pool->num_avail_blocks)++;

	/* 
	The for loop creates the n number of blocks of the required block size with the allignment bytes adjusted to the memory
	Increments the available block counter
	*/

	for(i=0;i<pool->total_num_blocks;i++){
		
		new_blk = (struct dll_block*)malloc(sizeof(struct dll_block));
		if(new_blk == NULL){
			printf("--------- Malloc() Error : Block Creation ---------\n");	
			return 0;
		}

		if(i == 0 ){
			dll_head = new_blk;
			new_blk->next = NULL;
			new_blk->prev = NULL;

		}
		else
		{
			cur->next = new_blk; 	
			new_blk->prev = cur;
			new_blk->next = NULL;
		}
				
		if(((int)(cur->data_ptr+block_size)%pool->alignment_bytes) == 0)
			new_blk->data_ptr = cur->data_ptr + block_size;
		else
			new_blk->data_ptr = cur->data_ptr + block_size + alignment - ((int)(cur->data_ptr + block_size) % pool->alignment_bytes);
		
		cur = new_blk;
		
		//printf("--------- Block %d Creating---------\n", i);
		(pool->num_avail_blocks)++;
	}

	// The memory address is stored as the data pointer to the physical location
	pool->pool_head->prev = dll_head;
	pool->pool_head->data_ptr = NULL;			
	pool->pool_head->next = NULL;

	printf("\nTotal number available Blocks after Pool Creation: %d \n", pool->total_num_blocks);

//	printf("\nCreation Block Head is :  %d\n", (int)pool->pool_head->data_ptr);
//	*/
	return pool;
}

/*
alloc_align_block method allocates a block pool of memory that was created by the create_block_pool
Returns the head of the DLL as the free block whenever there's a function call
Decrements the available block counter
*/

void* alloc_align_block(struct block_pool* pool)
{

	if(pool->num_avail_blocks == 0){
		printf("\nmemory not available...");
		return NULL;
	}

	struct dll_block *blk, *free_head, *used_head;


	blk = NULL;

	free_head = pool->pool_head->prev;
	used_head = pool->pool_head->next;		

	blk = free_head;
	free_head = free_head->next;

	if(used_head == NULL)
	{
		used_head = blk;
		used_head->next = NULL;
		used_head->prev = NULL;
	}else
	{	
		blk->next = used_head;
		used_head->prev = blk;	
		used_head = blk;
	}

	(pool->num_avail_blocks)--;

	pool->pool_head->prev = free_head ;
	pool->pool_head->next = used_head;
	
//	printf("\nThe memory block allocated is :  %p\n", blk->data_ptr);
//	printf("\nMemory Head after allocation is :  %p\n", used_head->data_ptr);
	//printf("\nAlligned Memory assigned  :  %lf\n", ((float)blk->data_ptr/(float)pool->alignment_bytes));
	printf("\nAvailable Blocks after allocation: %d \n", pool->num_avail_blocks);

// */	

	return blk->data_ptr;
}

/*
free_align_block method deallocates a block pool of memory that was assigned by the alloc_align_block
Toggles through the DLL to locate the address to deallocate
The deallocated memory block is added to the head of the DLL whenever there's a function call
Increments the available block counter
*/
void free_align_block(struct block_pool* pool, void* blk_dataptr)
{
	
	if(pool->num_avail_blocks >= pool->total_num_blocks){
		printf("cannot free memory...");
		return;
	}

	struct dll_block *cur, *free_head, *used_head ;
	
	free_head = pool->pool_head->prev;
	used_head = pool->pool_head->next;

	cur = used_head;

//	printf("find %p",blk_dataptr);

	while(cur->next != NULL){
//		printf("%p \n",cur->data_ptr);

		if(blk_dataptr == cur->data_ptr)
			break;			
		cur = cur->next;
//		printf("%p \n",cur->data_ptr);
	}

	if(blk_dataptr != cur->data_ptr && cur->next == NULL){
		printf ("\nmemory adress not found!!!");
		return;
	}


	if(cur->next == NULL && cur->prev == NULL)
		used_head = NULL;
	else{
		if(cur->next != NULL)
			cur->next->prev = cur->prev;
		if(cur->prev != NULL)
			cur->prev->next = cur->next;
		else{
			used_head = cur->next;
		}

	}

	if(free_head != NULL)
		free_head->prev = cur;
	cur->next = free_head;
	free_head = cur;

	(pool->num_avail_blocks)++;

//	printf("used_head %p \n",used_head->data_ptr);

	pool->pool_head->prev = free_head ;
	pool->pool_head->next = used_head;

//	printf("\nThe memory block deallocated is :  %d\n", (int)cur->data_ptr);
//	printf("\nMemory Head after deallocation is :  %d\n", free_head->data_ptr);
	printf("\nAvailable Blocks after deallocation: %d \n\n", pool->num_avail_blocks);
		
}

/*
int main(int argc, char *argv[])
{
	
	int num_blks = 0, blk_size = 0, align = 0;
	struct	block_pool *blk_pool;
	void* assign,*assign1,*assign2,*assign3;

	printf("--------- CS503-Lab 1: Aligned Block Allocator ---------\n");	
	printf("Enter the following inputs\n");		
	printf("Enter the Number of blocks\n");
	scanf("%d", &num_blks);
	printf("Enter the Block Size of each block\n");
	scanf("%d", &blk_size);
	printf("Enter the Allignment bytes for each block\n");
	scanf("%d", &align);


	if(!(blk_pool = create_block_pool(num_blks, blk_size, align))){
		printf("--------- FnCall Error : Create block pool ---------\n");				
		return 0;	
	}
//	printf("\npol add %p", blk_pool );

	assign = alloc_align_block(blk_pool)	;

//	if(!(assign = alloc_align_block(blk_pool))){
//		printf("--------- FnCall Error : Assign Alligned blocks ---------\n");
//		return 0;	
//	}				
	if((unsigned long)assign%(unsigned long)align == 0 )
		printf("\nalligned %ld  %p", (unsigned long)assign, assign);
	else
		printf("\n%ld, %d",(unsigned long)assign, align);

	assign1 = alloc_align_block(blk_pool)	;

	if((unsigned long)assign1%(unsigned long)align == 0 )
		printf("\nalligned %ld  %p", (unsigned long)assign1, assign1 );
	else
		printf("\n%ld, %d",(unsigned long)assign1, align);

	free_align_block(pool, assign);

	assign2 = alloc_align_block(blk_pool)	;
//	printf("\n%ld, %d",(unsigned long)assign2, align);

	if((unsigned long)assign2%(unsigned long)align == 0 )
		printf("\nalligned %ld  %p", (unsigned long)assign2, assign2 );
	else
		printf("\n%ld, %d",(unsigned long)assign2, align);


	assign3 = alloc_align_block(blk_pool)	;
	printf("\n%ld, %d",(unsigned long)assign3, align);


	free_align_block(pool, assign2);
	free_align_block(pool, assign2);
	free_align_block(pool, assign2);
/*
	if((unsigned long)assign3%(unsigned long)align == 0 )
		printf("\nalligned %ld  %p", (unsigned long)assign3, assign3 );
	else
		printf("\n%ld, %d",(unsigned long)assign3, align);




	printf("\nThe memory block allocated is :  %d\n", (int)assign);

	printf("\nThe memory block deallocated is :  %d\n", (int)assign);
// 
	return 0;

}
*/
