/*
OPENING ACCOUNT=A
BILL PAYMENT =B
CASH P[AYMENT=C

WE can assign fix value to each if a brust time is 10 if b than brust time is 2 if c than brust time is 5

Using Shortest job first algorithum in c++

Turn around time 2,5,15
 */

#include<iostream>
using namespace std;

struct Process 
{
    //Arrival time variable used for storing process arrival time it is assign manually
    int arrival_time;
    //burst_time variable used for storing process burst_time  it is depend on task values these values  assign manually
    int burst_time;
    //waiting_time  variable used for storing process waiting_time   it is assign manually
    int waiting_time;
    //bturn_around_time variable used for storing process turn_around_time  is equal to brust time and waiting time
    int turn_around_time;
    //task variable used for storing process task for calculating brust time  it is assign manually
    char task;
};
void calculate_brust_time(Process *p,int n)
{
  // we are assign the brust time to each process by using its task value The assigning value is depend on our requirment 
  for(int i=0;i<n;i++)
  {
      // assgin value of a to brust time according to condition
      if(p[i].task=='a')
        {
           p[i].burst_time=10;
        }
     // assgin value of b to brust time according to condition
      else if(p[i].task=='b')
       {
          p[i].burst_time=2;
       }
       // assgin value of c to brust time according to condition
      else if(p[i].task=='c')
       {
        p[i].burst_time=5;
       }
       // if character doestnot match tan error generate 
       else
       {
        cout<<"Invalid character Value error are generated !!!!"<<endl;
       }
  }
}
void shortes_job_first_scheduling(Process*p,int n)
{
      for(int i=0;i<n;i++)
    {
        p[i].turn_around_time=p[i].burst_time+p[i].waiting_time;
    }

}
void assign_values_manually(Process *Processes)
{
    // assign arrival time to each proceess according to the requirment
    Processes[0].arrival_time=1;
    Processes[1].arrival_time=0;
    Processes[2].arrival_time=2;
    // assign waiting time to each proceess according to the requirment
    Processes[0].waiting_time=0;
    Processes[1].waiting_time=2;
    Processes[2].waiting_time=5;
    // assign  task  to each proceess for calculate brust time according to the requirment
    Processes[0].task='b';
    Processes[1].task='c';
    Processes[2].task='a';
}
int main()
{
    Process Processes[3];
    int n=3;
    // Assign values to each proceess manually like arrival time , brsut time and its task value also
    assign_values_manually(Processes);
    //Assign brust time according to its task 
    calculate_brust_time(Processes,n);
    //This one use for calculating turn_around time using waiting time and brust time 
    shortes_job_first_scheduling(Processes,n);
     

    // We arec desplaying all values on terminal such as process id , arrival time ,task, waiting time and turn around time
    cout<<"Person   |   Arrival time  | task   | waiting time  | Turn around time "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<i+1<<"        |  "<<Processes[i].arrival_time<<"              |  "<<Processes[i].task<<"      |  "<<Processes[i].waiting_time<<"            |  "<<Processes[i].turn_around_time<<endl;
  
    }
    return 0;
    cout<<Processes;
}



