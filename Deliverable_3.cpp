#include <iostream>
using namespace std;

const int MEMORY_SIZE = 1024;
const int FIRST_FIT = 1;
const int BEST_FIT = 2;

// each node of the free list stores one free region of memory
class FreeBlock{
public:
    int start;      
    int size;        
    FreeBlock* next; 
};

class MemoryAllocator{
private:
    char memory[MEMORY_SIZE]; 
    FreeBlock* head;        
    int strategy;             
    int success_Count;         
    int fail_Count;

public:
    // in the beginning the whole memory is free  so the list has only one node covering everything
    MemoryAllocator(int strat){
        head = new FreeBlock;
        head->start = 0;
        head->size = MEMORY_SIZE;
        head->next = NULL;
        strategy = strat;
        success_Count = 0;
        fail_Count = 0;
    }

    // allocate memory from a chosen block  this part is same for both strategies returns the starting position of the allocated memory

    int take_FromBlock(FreeBlock* block, FreeBlock* prev, int size){
        int allocatedStart = block->start;

        if (block->size == size){
            // exact match, remove this node from the list
            if (prev == NULL){
                head = block->next;
            }
            else{
                prev->next = block->next;
            }
            delete block;
        }
        else{
            // block is bigger than needed, split it by shrinking the node
            block->start = block->start + size;
            block->size = block->size - size;
        }

        success_Count++;
        return allocatedStart;
    }

    // allocate using the selected strategy returns -1 if no block is big enough
    int allocate(int size){
        FreeBlock* temp = head;
        FreeBlock* prev = NULL;

        if (strategy == FIRST_FIT){
            // take the first block that is big enough
            while (temp != NULL){
                if (temp->size >= size){
                    return take_FromBlock(temp, prev, size);
                }
                prev = temp;
                temp = temp->next;
            }
        }
        else{
            // best fit, check the whole list and remember the  smallest block that is still big enough
            FreeBlock* best = NULL;
            FreeBlock* bestPrev = NULL;

            while (temp != NULL){
                if (temp->size >= size){
                    if (best == NULL || temp->size < best->size){
                        best = temp;
                        bestPrev = prev;
                    }
                }
                prev = temp;
                temp = temp->next;
            }

            if (best != NULL){
                return take_FromBlock(best, bestPrev, size);
            }
        }

        // nothing was big enough
        cout << "Allocation failed! No free block of size " << size << " available." << endl;
        fail_Count++;
        return -1;
    }

    // return a block of memory back to the free list  the list must stay sorted by starting address

    void free(int start, int size){
        FreeBlock* node = new FreeBlock;
        node->start = start;
        node->size = size;
        node->next = NULL;

        // case 1, list is empty or the new block comes before the head
        if (head == NULL || start < head->start){
            node->next = head;
            head = node;
            return;
        }

        // case 2, walk until we find the right spot stop when the next block starts after our new block

        FreeBlock* temp = head;
        while (temp->next != NULL && temp->next->start < start){
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
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
    int count_FreeBlocks(){
        int count = 0;
        FreeBlock* temp = head;
        while (temp != NULL){
            count++;
            temp = temp->next;
        }
        return count;
    }

    // add up the size of every free block
    int total_FreeMemory(){
        int total = 0;
        FreeBlock* temp = head;
        while (temp != NULL){
            total = total + temp->size;
            temp = temp->next;
        }
        return total;
    }

    // find the biggest single free block
    int largest_FreeBlock(){
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

    // final statistics asked in deliverable 3
    void displayStats(){
        cout << "Number of free blocks  : " << count_FreeBlocks() << endl;
        cout << "Total free memory      : " << total_FreeMemory() << " bytes" << endl;
        cout << "Largest free block     : " << largest_FreeBlock() << " bytes" << endl;
        cout << "Successful allocations : " << success_Count<< endl;
        cout << "Failed allocations     : " << fail_Count << endl;
    }
};

// the fixed test sequence given in the assignment prints the free list after every step
void runTest_Sequence(MemoryAllocator &alloc){
    int r;

    r = alloc.allocate(100);
    cout <<"allocate(100) returned"<< r<< endl;
    alloc.displayFreeList();
    cout << endl;

    r = alloc.allocate(250);
    cout <<"allocate(250) returned" <<r << endl;
    alloc.displayFreeList();
    cout << endl;

    r = alloc.allocate(80);
    cout <<"allocate(80) returned"<< r << endl;
    alloc.displayFreeList();
    cout << endl;

    alloc.free(100, 250);
    cout <<"free(100, 250)"<< endl;
    alloc.displayFreeList();
    cout << endl;

    r = alloc.allocate(200);
    cout <<"allocate(200) returned" <<r << endl;
    alloc.displayFreeList();
    cout << endl;

    r = alloc.allocate(500);
    cout <<"allocate(500) returned"<< r<< endl;
    alloc.displayFreeList();
    cout << endl;

    alloc.free(0, 100);
    cout <<"free(0, 100)"<< endl;
    alloc.displayFreeList();
    cout << endl;

    r = alloc.allocate(50);
    cout<<"allocate(50) returned"<<r<< endl;
    alloc.displayFreeList();
    cout<<endl;
}

int main(){
    cout <<"Memory Size = "<< MEMORY_SIZE << " bytes" << endl;
    cout << endl;

    cout <<"FIRST FIT"<<endl;
    MemoryAllocator firstFit(FIRST_FIT);
    cout <<"Initial state"<< endl;
    firstFit.displayFreeList();
    cout << endl;
    runTest_Sequence(firstFit);
    cout <<"Final statistics"<< endl;
    firstFit.displayStats();
    cout << endl;

    // bonus part same sequence with best fit
    cout << "BEST FIT " << endl;
    MemoryAllocator bestFit(BEST_FIT);
    cout <<"Initial state"<<endl;
    bestFit.displayFreeList();
    cout << endl;
    runTest_Sequence(bestFit);
    cout <<"Final statistics"<<endl;
    bestFit.displayStats();

    return 0;
}