#include <iostream>
using namespace std;

struct Node
{
    int size;
    bool isAllocated;
    int processId; // Add processId member
    Node *next;
};

class Memory_Manager
{
private:
    Node *head;

public:
    Memory_Manager(int totalMemory)
    {
        head = create_block(totalMemory, false);
    }

    ~Memory_Manager()
    {
        Node *currentBlock = head;
        while (currentBlock != nullptr)
        {
            Node *nextBlock = currentBlock->next;
            delete currentBlock;
            currentBlock = nextBlock;
        }
    }
    void allocate_process(int processId, int processSize)
    {
        Node *currentBlock = find_free_block(processSize);
        if (currentBlock != nullptr)
        {
            split_block(currentBlock, processSize);
            currentBlock->isAllocated = true;
            currentBlock->processId = processId; 
            cout << "Allocated Process P" << processId << " with " << processSize << " KB" << endl;
        }
        else
        {
            cout << "Insufficient memory to allocate Process P" << processId << " with " << processSize << " KB" << endl;
        }
    }

    void deallocate_process(int processId)
    {
        Node *currentBlock = head;
        Node *prevBlock = nullptr;

        while (currentBlock != nullptr)
        {
            if (currentBlock->isAllocated && currentBlock->processId == processId)
            {
                
                currentBlock->isAllocated = false;
                cout << "Deallocated Process P" << processId << " with " << currentBlock->size << " KB" << endl;               
                if (prevBlock != nullptr)
                {
                    prevBlock->next = currentBlock->next;
                }
                else
                {
                    head = currentBlock->next;
                }
                currentBlock->next = head;
                head = currentBlock;
                return;
            }
            prevBlock = currentBlock;
            currentBlock = currentBlock->next;
            
        }
        cout << "Process P" << processId << " not found in memory" << endl;
    }
    void display_memory_state()
    {
        Node *currentBlock = head;
        cout << "Memory State:" << endl;
        while (currentBlock != nullptr)
        {
            cout << "Block Size: " << currentBlock->size << " | Allocated: " << (currentBlock->isAllocated ? "Yes" : "No") << " | Process ID: " << currentBlock->processId << endl;
            currentBlock = currentBlock->next;
        }
        cout << "----------------------" << endl;
    }
    Node *find_free_block(int size)
    {
        Node *currentBlock = head;
        while (currentBlock != nullptr)
        {
            if (!currentBlock->isAllocated && currentBlock->size >= size)
            {
                return currentBlock;
            }
            currentBlock = currentBlock->next;
        }
        return nullptr;
    }

    void split_block(Node *block, int size)
    {
        
        if (block->size > size)
        {
            Node *newBlock = create_block(block->size - size, false);
            newBlock->next = block->next;
            block->size = size;
            block->next = newBlock;
        }
    }

    Node *create_block(int size, bool isAllocated)
    {
        Node *newBlock = new Node;
        newBlock->size = size;
        newBlock->isAllocated = isAllocated;
        newBlock->processId = -1;
        newBlock->next = nullptr;
        return newBlock;
    }
};

int main()
{
    Memory_Manager memoryManager(1000);

  
    memoryManager.allocate_process(1, 200);
    memoryManager.display_memory_state();

    memoryManager.allocate_process(2, 300);
    memoryManager.display_memory_state();

    memoryManager.allocate_process(3, 500);
    memoryManager.display_memory_state();

    memoryManager.allocate_process(4, 500);
    memoryManager.display_memory_state();

    memoryManager.deallocate_process(2);
    memoryManager.display_memory_state();

 return 0;
}
