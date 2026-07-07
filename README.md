# CS293 Extra Credit Project

Memory Allocator using a Free List.

This project manages a fixed memory pool of 1024 bytes. The free space is stored in a linked list. Each node of the list keeps the starting position and size of one free region.

## How to build and run

``` bash
g++ -o allocator allocator.cpp
./allocator
```

## Files

allocator.cpp contains the FreeBlock class, the MemoryAllocator class and the main function.

explanation.md is the short write up about the data structure.

## Progress

Deliverable 1 (July 4) is done. It builds the free list and prints the number of free blocks, total free memory and the largest free block.

Deliverable 2 (July 8) is done. It adds the allocate function using the first fit strategy. The demo in main shows several successful allocation and exact match case where the free block is removed from the list and failed allocation when no block is big enough.

## AI tools used

As allowed in the project guidelines, I used an AI assistant (Claude) to help me while writing this code. I have gone through the code myself and understand how it works.