#include <iostream>
using namespace std;

const int MEMORY_SIZE = 1024;

// each node of the free list stores one free region of memory
class FreeBlock{
public:
    int start;       
    int size;        
    FreeBlock* next; 
};

class MemoryAllocator{
private:
    char memory[MEMORY_SIZE]; // the memory pool we are managing
    FreeBlock* head;          

public:
    // in the beginning the whole memory is free and the list has only one node covering everything
    MemoryAllocator(){
        head = new FreeBlock;
        head->start = 0;
        head->size = MEMORY_SIZE;
        head->next = NULL;
    }

// Search the free list and allocate the first block that is large enough.
    int allocate(int size){
        FreeBlock* temp = head;
        FreeBlock* prev = NULL;

        while (temp != NULL){
            if (temp->size >= size){
                // remember where this block starts, this is what we return
                int allocStart = temp->start;
                if (temp->size == size){
                    // exact match, remove this node from the list
                    if (prev == NULL){
                        head = temp->next;
                    }
                    else{
                        prev->next = temp->next;
                    }
                    delete temp;
                }
                else{
                 // Split the block and keep the remaining free space.
                    temp->start = temp->start + size;
                    temp->size = temp->size - size;
                }
                return allocStart;
            }
            prev = temp;
            temp = temp->next;
        }

        // reached the end of the list, nothing was big enough
        cout << "Allocation failed No free block of size " << size << " available." << endl;
        return -1;
    }

    // print the free list
    void displayFreeList(){
        cout << "Free List: ";
        FreeBlock* temp = head;
        while (temp != NULL){
            cout << "[start=" << temp->start << ", size=" << temp->size << "] -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // count how many free blocks are in the list
    int countFreeBlocks(){
        int count = 0;
        FreeBlock* temp = head;
        while (temp != NULL){
            count++;
            temp = temp->next;
        }
        return count;
    }

    // add up the size of every free block
    int totalFreeMemory(){
        int total = 0;
        FreeBlock* temp = head;
        while (temp != NULL){
            total = total + temp->size;
            temp = temp->next;
        }
        return total;
    }

    // find the biggest single free block
    int largestFreeBlock(){
        int largest = 0;
        FreeBlock* temp = head;
        while (temp != NULL){
            if (temp->size > largest){
                largest = temp->size;
            }
            temp = temp->next;
        }
        return largest;
    }
};

int main(){
    cout << "Memory Size = " << MEMORY_SIZE << " bytes" << endl;
    cout << endl;

    MemoryAllocator allocator;

    cout << "Initial state of memory:" << endl;
    allocator.displayFreeList();
    cout << endl;

    // some successful allocations
    int a = allocator.allocate(100);
    cout << "allocate(100) returned " << a << endl;
    allocator.displayFreeList();
    cout << endl;

    int b = allocator.allocate(250);
    cout << "allocate(250) returned " << b << endl;
    allocator.displayFreeList();
    cout << endl;

    int c = allocator.allocate(80);
    cout << "allocate(80) returned " << c << endl;
    allocator.displayFreeList();
    cout << endl;

// This allocation exactly matches the free block, so remove it from the list.
    int d = allocator.allocate(594);
    cout << "allocate(594) returned " << d << endl;
    allocator.displayFreeList();
    cout << endl;

    // failure case, the memory is completely full now
    cout << "Trying to allocate 50 bytes when memory is full:" << endl;
    int e = allocator.allocate(50);
    cout << "allocate(50) returned " << e << endl;
    allocator.displayFreeList();
    cout << endl;

    cout << "Number of free blocks : " << allocator.countFreeBlocks() << endl;
    cout << "Total free memory     : " << allocator.totalFreeMemory() << " bytes" << endl;
    cout << "Largest free block    : " << allocator.largestFreeBlock() << " bytes" << endl;

    return 0;
}