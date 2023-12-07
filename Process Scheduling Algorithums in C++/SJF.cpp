#include<iostream>
using namespace std;

struct Process {
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turn_around_time;
};
void sort_process_by_brust_time(Process*  processes, int n) {

    for (int i = 0; i < n - 1; i++)
     {
        for (int j = i+1; j < n ; j++) 
        {
            if (processes[i].burst_time > processes[j].burst_time)
             {
                swap(processes[i], processes[j]);
            }
        }
    }
}
void shortes_job_first_scheduling(Process*processes,int n)
{
    sort_process_by_brust_time(processes,n);
    int current_time=0;
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            processes[i].waiting_time=0;
        }
        else
        {
            processes[i].waiting_time=current_time-processes[i].arrival_time;

        }
        current_time=current_time+processes[i].burst_time;
        processes[i].turn_around_time=current_time-processes[i].arrival_time;
    }

}
int main()
{
    Process Processes[]=
    {
        {0,5},
        {1,3},
        {2,4}
    };
    int n=3;
    shortes_job_first_scheduling(Processes,n);
    for(int i=0;i<n;i++)
    {
        cout<<"Process: "<<i+1<<"    waiting_time :"<<Processes[i].waiting_time<<"  Turn_around_time :"<<Processes[i].turn_around_time<<endl;
    }
    return 0;
    
}







