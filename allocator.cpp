// CS293 Extra Credit Project
// Deliverable 1 : Building the Free List
// Memory Allocator using a linked list of free blocks

#include <iostream>
using namespace std;

const int MEMORY_SIZE = 1024;

// each node of the free list stores one free region of memory
class FreeBlock
{
public:
    int start;       // where the free block starts
    int size;        // how many bytes are free here
    FreeBlock* next; // pointer to the next free block
};

class MemoryAllocator
{
private:
    char memory[MEMORY_SIZE]; // the memory pool we are managing
    FreeBlock* head;          // first node of the free list

public:
    // in the beginning the whole memory is free
    // so the list has only one node covering everything
    MemoryAllocator()
    {
        head = new FreeBlock;
        head->start = 0;
        head->size = MEMORY_SIZE;
        head->next = NULL;
    }

    // print the free list
    void displayFreeList()
    {
        cout << "Free List: ";
        FreeBlock* temp = head;
        while (temp != NULL)
        {
            cout << "[start=" << temp->start << ", size=" << temp->size << "] -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // count how many free blocks are in the list
    int countFreeBlocks()
    {
        int count = 0;
        FreeBlock* temp = head;
        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // add up the size of every free block
    int totalFreeMemory()
    {
        int total = 0;
        FreeBlock* temp = head;
        while (temp != NULL)
        {
            total = total + temp->size;
            temp = temp->next;
        }
        return total;
    }

    // find the biggest single free block
    int largestFreeBlock()
    {
        int largest = 0;
        FreeBlock* temp = head;
        while (temp != NULL)
        {
            if (temp->size > largest)
            {
                largest = temp->size;
            }
            temp = temp->next;
        }
        return largest;
    }
};

int main()
{
    cout << "Memory Size = " << MEMORY_SIZE << " bytes" << endl;
    cout << endl;

    MemoryAllocator allocator;

    cout << "Initial state of memory:" << endl;
    allocator.displayFreeList();
    cout << endl;

    cout << "Number of free blocks : " << allocator.countFreeBlocks() << endl;
    cout << "Total free memory     : " << allocator.totalFreeMemory() << " bytes" << endl;
    cout << "Largest free block    : " << allocator.largestFreeBlock() << " bytes" << endl;

    return 0;
}