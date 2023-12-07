#include <iostream>
using namespace std;
class Partition
{
public:
    int size;
    bool isAllocated;
    Partition(int size)
    {
        this->size = size;
        this->isAllocated = false;
    }
};
class Process
{
public:
    int processId;
    int processSize;
    Partition *partition;
    Process(int processId, int processSize)
    {
        this->processId = processId;
        this->processSize = processSize;
        this->partition = nullptr;
    }   
};
class Memory_Manager
{
private:
    Partition **partitions;
    int numPartitions;
public:
    Memory_Manager(Partition *partitions[], int numPartitions)
    {
        this->partitions = partitions;
        this->numPartitions = numPartitions;
    }
    void allocate_process(Process *process)
    {
        for (int i = 0; i < numPartitions; i++)
        {
            if (!partitions[i]->isAllocated && partitions[i]->size >= process->processSize)
            {
                partitions[i]->isAllocated = true;
                process->partition = partitions[i];
                break;
            }
        }
        if (process->partition == nullptr)
        {
            cout << "Insufficient memory to allocate process " << process->processId << endl;
        }
    }
    void display(Process *processes[], int numProcesses)
    {
        cout << "Processes and their space usage:" << endl;
        for (int i = 0; i < numProcesses; i++)
        {
            cout << "Process ID: " << processes[i]->processId << ", Process Size: " << processes[i]->processSize
                 << ", Allocated to Partition: " << (processes[i]->partition ? "Yes" : "No") << endl;
        }
    }
    void deallocate_process(Process *process)
    {
        if (process->partition != nullptr)
        {
            process->partition->isAllocated = false;
            process->partition = nullptr;
        }
    }
};

int main()
{
    Partition *partitions[] = {new Partition(250), new Partition(250), new Partition(250), new Partition(250)};
    int numPartitions = sizeof(partitions) / sizeof(Partition *);

    Memory_Manager memoryManager(partitions, numPartitions);

    Process *processes[] = {new Process(1, 200), new Process(2, 300), new Process(3, 500)};
    int numProcesses = sizeof(processes) / sizeof(Process *);

    for (int i = 0; i < numProcesses; i++)
    {
        memoryManager.allocate_process(processes[i]);
    }

    memoryManager.display(processes, numProcesses);

    for (int i = 0; i < numProcesses; i++)
    {
        memoryManager.deallocate_process(processes[i]);
    }

    for (int i = 0; i < numPartitions; i++)
    {
        delete partitions[i];
    }

    for (int i = 0; i < numProcesses; i++)
    {
        delete processes[i];
    }

    return 0;
}
