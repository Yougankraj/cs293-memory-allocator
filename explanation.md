# Explanation of the Data Structure

The allocator manages one big block of 1024 bytes. Instead of remembering which bytes are used, it remember which parts are free. All the free parts are stored in a linked list called free list. Any part of memory that is not in the free list is treated as allocated.

## FreeBlock class
Each node of the list is a FreeBlock object. It has three things:-

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
In the next deliverables, free blocks will be created and removed all the time and when memory is allocated and freed. A linked list  insert or remove a block anywhere without shifting other elements like an array would need. Also, when a block is bigger than the request size, we can just change its start and size to split it, which is very easy with this structure.

One more point is that largest free block is different from total free memory. After many allocation and free the memory becomes disconnected. The total free memory can be big but if the every single block is small, a large allocation will still fail. That is why both functions are needed.

## Deliverable 2, the allocate function

For allocation I went with first fit since that is what the assignment asks. The idea is simple start at the head and keep moving until i find a block where size >= requested size. The first one that fits, I take it.

While searching I keep two pointers, temp and prev. temp is the block i am currently checking and prev is the one behind it. The reason I need prev is for the case where a node gets removed, because then the node behind it has to be linked to the node after it otherwise the list breaks.

Three things can happen:

Case 1, the block is bigger than what was asked. Here I split it. I dont make any new node, I just push start ahead by the requested size and cut size down by the same amount. So the same node now stands for the leftover part only. The front part is the allocated memory.

Case 2, the block is the exact size. Then the whole node goes away. If it was the head then head just moves to the next node, otherwise prev->next points to temp->next. Then I delete the node.

Case 3, nothing in the list is big enough. Then i print that the allocation failed and return -1.

For case 1 and 2 the function return where the block used to start since that is the address the user get. I store this in a variable before touching the node because in the split case start changes and I would return the wrong value.

allocate is O(n) since in the worst case it checks every free block. Also an allocation can fail even when total free memory is enough, if the free memory is in small scattered piece no single piece fits the request. This is fragmentation.
