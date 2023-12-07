#include<iostream>
using namespace std;

struct partition 
{
    int id;
    bool allocated;
    int size;
    int process_id;
};

class partition_manage 
{
private:

    partition *partitions;
    int total_partitions;
    int total_processes;

public:

    partition_manage(int memory_size, int no_of_process) 
    {

        int partition_size = 256; 
        total_partitions = memory_size;
        total_processes = no_of_process;
        partitions = new partition[total_partitions];

      

        for (int i = 0; i < total_partitions; ++i) 
        {
            partitions[i].id = i + 1;
            partitions[i].allocated = false;
            partitions[i].size = partition_size;
            partitions[i].process_id = -1;
        }

    }
    ~partition_manage() 

    {
        delete[] partitions;
    }

    void allocation(int process_id, int required_size) 

    {
        bool allocated = false;
        for (int i = 0; i < total_partitions; i++) 
        {
            if (!partitions[i].allocated && partitions[i].size >= required_size) 
            {
                partitions[i].allocated = true;
                partitions[i].process_id = process_id;
                allocated = true;
                break;
            }
        }
        if (!allocated) 
        {
            cout << "Memory allocation failed for process " << process_id << " of size " << required_size << endl;
        }
    }

    void deallocation(int process_id) 
    
    {
        for (int i = 0; i < total_partitions; ++i) 
        {
            if (partitions[i].allocated && partitions[i].process_id == process_id) 
            {
                partitions[i].allocated = false;
                partitions[i].process_id = -1;
            }
        }
        cout<<"process id   "<<process_id<<"  Deallocated successfully"<<endl;
    }

    void partition_table() 
    {
        cout << "Partition Table:" << endl;
        for (int i = 0; i < total_partitions; ++i) 
        {
            cout << "Partition ID: " << partitions[i].id << " - ";
            if (partitions[i].allocated) 
            {
                cout << "Allocated to Process " << partitions[i].process_id << " - Size: " << partitions[i].size << endl;
            }
            else 
            {
                cout << "Free - Size: " << partitions[i].size << endl;
            }
        }
    }

   
};

int main() 
{
    int no_of_partitons =4 ;
    int no_of_process = 4;
    partition_manage obj(no_of_partitons, no_of_process);
                //process id,size of process
    obj.allocation(1, 200);
    obj.allocation(2, 400);
    obj.allocation(3, 178);
    obj.allocation(4, 145);
    obj.allocation(5, 90);
    obj.allocation(6, 40);
    obj.partition_table();
    
    obj.deallocation(3);
    obj.partition_table();

    return 0;
}
