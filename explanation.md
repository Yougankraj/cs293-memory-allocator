# Explanation of the Data Structure

The allocator manages one big block of 1024 bytes. Instead of remembering which bytes are used, it remembers which parts are free. All the free parts are stored in a linked list called the free list. Any part of memory that is not in the free list is treated as allocated.

## FreeBlock class

Each node of the list is a FreeBlock object. It has three things:

1. start, which tells where the free region begins inside the pool
2. size, which tells how many bytes are free from that point
3. next, which points to the next free block in the list

start is just an index number from 0 to 1023, not an actual pointer. This makes it easy to print and match with the address ranges shown in the assignment.

## MemoryAllocator class

This class holds the memory pool (a char array of 1024 bytes) and the head pointer of the free list. When the program starts, the whole pool is free, so the constructor creates one single node:

Free List: [start=0, size=1024] -> NULL

## Functions

displayFreeList goes through the list from head to the end and prints every node in the format [start=s, size=z]. It ends with NULL.

countFreeBlocks walks the list and counts the nodes.

totalFreeMemory walks the list and adds up the size of every node.

largestFreeBlock walks the list and keeps track of the biggest size it has seen.

All four functions just travel through the list one node at a time, so they are simple loops.

## Why a linked list

In the next deliverables, free blocks will be created and removed all the time when memory is allocated and freed. A linked list lets us insert or remove a block anywhere without shifting other elements like an array would need. Also, when a block is bigger than the requested size, we can just change its start and size to split it, which is very easy with this structure.

One more point is that largest free block is different from total free memory. After many allocations and frees the memory becomes fragmented. The total free memory can be big but if every single block is small, a large allocation will still fail. That is why both functions are needed.