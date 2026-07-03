# CS293 Extra Credit Project

Memory Allocator using a Free List.

This project manages a fixed memory pool of 1024 bytes. The free space is stored in a linked list. Each node of the list keeps the starting position and size of one free region.

## How to build and run

You need g++ installed.

```
g++ -o allocator allocator.cpp
./allocator
```

On Windows you can use MinGW with the same commands, or run it in any online C++ compiler.

## Files

allocator.cpp contains the FreeBlock class, the MemoryAllocator class and the main function.

explanation.md is the short write up about the data structure.

## Progress

Deliverable 1 (July 4) is done. It builds the free list and prints the number of free blocks, total free memory and the largest free block.

Deliverable 2 (allocate with first fit) and Deliverable 3 (free and final stats) will be added next.

## AI tools used

As allowed in the project guidelines, I used an AI assistant (Claude) to help me while writing this code. I have gone through the code myself and understand how it works.