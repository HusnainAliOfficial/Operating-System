#include<iostream>
using namespace std;
struct process{
    int pid;
    int arrive_time;
    int brust_time;
    int waiting_time;;
    int turnaround_time;
    process *next;
};
process* create_process_node(int new_id,int new_arrival_time,int new_brust_time)
{
     process * new_node=new process;
     new_node->pid=new_id;
     new_node->arrive_time=new_arrival_time;
     new_node->brust_time=new_brust_time;
     new_node->waiting_time=0;
     new_node->turnaround_time=0;
     new_node->next=NULL; 
      return new_node;
}
void insert_process_node(process*head,process* new_node)
{
    if(head==NULL)
    {
        head=new_node;
        return;
    }
    process*cureent =head;
    while(cureent->next!=NULL)
    {
        cureent=cureent->next;
    }
 
    cureent->next=new_node;
     
}

void calculate_waiting_time(process*head)
{
    process* current=head;
    int total_waiting_time=0;
    while(current!=NULL)
    {
        current->waiting_time=total_waiting_time;
        total_waiting_time+=current->brust_time;
        current=current->next;

    }

}
void calculate_turnaround_time(process*head)
{
     process* current=head;
      while(current!=NULL)
      {
   current->turnaround_time=current->waiting_time+current->brust_time;
   current=current->next;
      }
}

void fcfs(process*head)
{
    calculate_waiting_time(head);
    calculate_turnaround_time(head);
    cout<<"FcFS scheduling algorithum..............................."<<endl;
    cout<<"process id\tBrust time\tArrival time\twaiting time\tturn around time"<<endl;
    process*current=head;
    while(current!=NULL)
    {
        cout<<"p"<<current->pid<<"\t\t\t"<<current->brust_time<<"\t\t"<<current->arrive_time<<"\t\t"<<current->waiting_time<<"\t\t"<<current->turnaround_time<<endl;
        current=current->next;
    }
}
int main()
{
     process * head=NULL;
     head=create_process_node(1,5,0);
     insert_process_node(head,create_process_node(2,6,1));
     insert_process_node(head,create_process_node(3,9,2));
     fcfs(head);
     return 0;
}