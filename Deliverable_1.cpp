    #include <iostream>
    using namespace std;

    #define MEMORY_SIZE  1024

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

    public:
        // in the beginning the whole memory is free so the list has only one node cover everything
        MemoryAllocator(){
            head = new FreeBlock;
            head->start = 0;
            head->size = MEMORY_SIZE;
            head->next = NULL;
        }

        // print the free list
        void display_FreeList(){
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
    };

    int main(){
        cout << "Memory Size = " << MEMORY_SIZE << " bytes" << endl;
        cout << endl;

        MemoryAllocator allocator;

        cout << "Initial state of memory: " << endl;
        allocator.display_FreeList();
        cout << endl;

        cout << "Number of free blocks: " << allocator.count_FreeBlocks() << endl;
        cout << "Total free memory: " << allocator.total_FreeMemory() << " bytes" << endl;
        cout << "Largest free block: " << allocator.largest_FreeBlock() << " bytes" << endl;
        
        return 0;
    }