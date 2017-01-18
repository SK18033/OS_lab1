/*
=============================================================================

CS 50300 Operating Systems Lab1 - Alligned Memory Allocator

Alloc.c Source code		

Kartik Sooji (ksooji)

=============================================================================
*/


The purpose of the lab was to simulate the malloc() and free() functions by allocating and deallocating memory in blocks as the operating system assigns the same for any program or process.

There are 3 functionalities that are supported by the program

1) Create_Block_Pool

	This method returns a large chunk of memory that created as the user specifies the required number of blocks, the amount of bytes that needs to be allocated to each block and the bytes that needs to be alligned for each block starting address. The method contains runs a loop that creates individual blocks and adds the newly created alligned blocks to the doubly linked list that.


2) Alloc_Aligned_Block

	This method assigns the dll head as the assigned blocks. There are two reference pointers that store the heads for the used and free blocks in the dll and returns the void* reference of the free alligned block to the user


3) Free_Aligned_block

	This method dellocates the memory from the user and returns the same to the block pool which is added to the head of the DLL. Similar to alloc allign which uses free and used in order to maintain the free list.



Exceution Steps :

1) Change the current working directory to the source code location
2) Make sure there is a ".c" file and a ".h" file
3) type makefile and hit enter
4) Once the program is done run make clean 
