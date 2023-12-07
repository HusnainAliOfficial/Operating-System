#include<iostream>
#include<algorithm>
using namespace std;

class Process {
public:
    int processID;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    Process* next;

    Process(int id, int arrival, int burst): processID(id), arrivalTime(arrival), burstTime(burst), waitingTime(0), turnaroundTime(0), next(nullptr) {}
};
class Scheduler 
{
public:
    Process* head;
    int timeQuantum;  
    Scheduler(int quantum = 0) : head(nullptr), timeQuantum(quantum) {}

    void addProcess(int id, int arrival, int burst) 
    {
        Process* newProcess = new Process(id, arrival, burst);
        if (!head) 
        {
            head = newProcess;
        } 
        else 
        {
            Process* current = head;
            while (current->next) 
            {
                current = current->next;
            }
            current->next = newProcess;
        }
    }

    void FCFS() 
    {
       
        int currentTime = 0;
        Process* current = head;

        while (current) 
        {
            current->waitingTime = max(0, currentTime - current->arrivalTime);
            currentTime += current->burstTime;
            current->turnaroundTime = current->waitingTime + current->burstTime;
            current = current->next;
        }
    }

 
    void SJF() 
    {
        
        if (!head) 
        {
            return;
        }       
        head = sort_all_processes(head);
        int currentTime = 0;
        Process* current = head;
        while (current) 
        {
            current->waitingTime = std::max(0, currentTime - current->arrivalTime);
            currentTime += current->burstTime;
            current->turnaroundTime = current->waitingTime + current->burstTime;
            current = current->next;
        }
    }

   
    void RR() 
    {
        if (!head || timeQuantum <= 0)
        {
            return;
        }
        Process* current = head;
        int currentTime = 0;
        while (current) 
        {
            if (current->burstTime > 0) 
            {
                int remainingTime = min(timeQuantum, current->burstTime);
                current->burstTime -= remainingTime;
                currentTime += remainingTime;
                current = current->next;
            } 
            else 
            {
                current = current->next;
            }
        }
    }

    void calculate_averages(float& avgWaitingTime, float& avgTurnaroundTime) 
    {
        Process* current = head;
        int numProcesses = 0;

        while (current)
        {
            avgWaitingTime += current->waitingTime;
            avgTurnaroundTime += current->turnaroundTime;
            numProcesses++;
            current = current->next;
        }

        avgWaitingTime /= numProcesses;
        avgTurnaroundTime /= numProcesses;
    }

    Process* sort_all_processes(Process* head) 
    {
        if (!head || !head->next) 
        {
            return head;
        }
        Process* middle = between_two_processes(head);
        Process* nextToMiddle = middle->next;
        middle->next = nullptr;
        Process* left =sort_all_processes(head);
        Process* right = sort_all_processes(nextToMiddle);
        return scheduling_sorting(left, right);
    }

    Process* between_two_processes(Process* head) 
    {
        if (!head) 
        {
            return nullptr;
        }
        Process* previous = head;
        Process* head_next = head->next;
        while (head_next) 
        {
            head_next = head_next->next;
            if (head_next) 
            {
                previous = previous->next;
                head_next = head_next->next;
            }
        }
        return previous;
    }

    Process* scheduling_sorting(Process* left, Process* right) 
    {
        Process dummy(0, 0, 0);
        Process* tail = &dummy;
        dummy.next = nullptr;

        while (true) 
        {
            if (!left) 
            {
                tail->next = right;
                break;
            }
            if (!right) 
            {
                tail->next = left;
                break;
            }

            if (left->burstTime <= right->burstTime) 
            {
                tail->next = left;
                left = left->next;
            } else 
            {
                tail->next = right;
                right = right->next;
            }
            tail = tail->next;
        }

        return dummy.next;
    }

    void displayProcesses() 
    {
        Process* current = head;
        cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
        while (current) 
        {
            cout << current->processID << "\t" << current->arrivalTime << "\t\t" << current->burstTime << "\t\t" << current->waitingTime << "\t\t" << current->turnaroundTime <<endl;
            current = current->next;
        }
    }
};
int main() {
    Scheduler scheduler;
    //First process name , second Arrival time ,third brust time 
    scheduler.addProcess(1, 0, 6);
    scheduler.addProcess(2, 1, 4);
    scheduler.addProcess(3, 2, 2);
    scheduler.addProcess(4, 3, 8);

    
    cout<<"First come first serve Scheduling :"<<endl;
    scheduler.FCFS();
    float avgWaitingTime_fcfs= 0;
    float avgTurnaroundTime_fcfs = 0;
    scheduler.calculate_averages(avgWaitingTime_fcfs, avgTurnaroundTime_fcfs);
    scheduler.displayProcesses();
    cout << "Average Waiting Time: " << avgWaitingTime_fcfs << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime_fcfs << endl;
    cout << "Process scheduling details:\n";



    cout<<"Shortest Job first Scheduling :"<<endl;

    scheduler.SJF();
    float avgWaitingTime_sjf= 0;
    float avgTurnaroundTime_sjf = 0;
    scheduler.calculate_averages(avgWaitingTime_sjf, avgTurnaroundTime_sjf);
    scheduler.displayProcesses();
    cout << "Average Waiting Time: " << avgWaitingTime_sjf << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime_sjf << endl;
    cout << "Process scheduling details:\n";
    



    cout<<"Round Robin Scheduling :"<<endl;
    scheduler.timeQuantum = 1; 
    scheduler.RR();
    float avgWaitingTime_RR= 0;
    float avgTurnaroundTime_RR= 0;
    scheduler.calculate_averages(avgWaitingTime_RR, avgTurnaroundTime_RR);
     scheduler.displayProcesses();
    cout << "Average Waiting Time: " << avgWaitingTime_RR << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime_RR <<endl;
    cout << "Process scheduling details:\n";
   

    float best_turnaround =min({avgTurnaroundTime_fcfs,avgTurnaroundTime_RR,avgTurnaroundTime_sjf});
    float best_waiting=min({avgWaitingTime_fcfs,avgWaitingTime_sjf,avgWaitingTime_RR});
   cout<<"Best Turnaround Time :"<<best_turnaround<<endl;
   cout<<"Best Waiting Time :"<<best_waiting<<endl;
    return 0;
}
