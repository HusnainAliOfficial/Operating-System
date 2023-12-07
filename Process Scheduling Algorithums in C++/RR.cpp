#include <iostream>
using namespace std;

class process
{

public:
    int pid;
    int arrival_time;
    int brust_time;
    int remaining_brust;
    int waiting_time;
    int turn_around_time;
    process *next;
    process(int id, int arrival, int brust)
    {
        pid = id;
        arrival_time = arrival;
        brust_time = brust;
        remaining_brust = brust;
        waiting_time = 0;
        turn_around_time = 0;
        next = nullptr;
    }
};
class round_robin_scheduler
{
private:
    process *head;
    int num_processes;
    int quantum;

public:
    round_robin_scheduler(int q) : head(nullptr), num_processes(0), quantum(q) {}
    void add_process(int pid, int arrival_time, int brust_time)
    {
        process *new_process = new process(pid, arrival_time, brust_time);
        if (!head)
        {
            head = new_process;
            head->next = head;
        }
        else
        {
            process *temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = new_process;
            new_process->next = head;
        }
        num_processes++;
    }
    void calculate_time()
    {
        int current_time = 0;
        process *current_process = head;
        while (num_processes > 0)
        {
            if (current_process->remaining_brust > 0)
            {
                if (current_process->remaining_brust > quantum)
                {
                    current_time += quantum;
                    current_process->remaining_brust -= quantum;
                }
                else
                {
                    current_time += current_process->remaining_brust;
                    current_process->waiting_time = current_time - current_process->arrival_time + current_process->brust_time;
                    current_process->remaining_brust = 0;
                    current_process->turn_around_time = current_process->waiting_time + current_process->brust_time;
                    num_processes--;
                }
            }
            current_process = current_process->next;
        }
    }
    void display()
    {
        cout << "PID\t Arrival time\t Brust time \t waiting time\tTurn around time" << endl;
        process *current_process = head;
        do
        {
            cout << current_process->pid << "\t\t" << current_process->arrival_time << "\t\t" << current_process->brust_time << "\t\t" << current_process->waiting_time << "\t\t" << current_process->turn_around_time << endl;
            current_process = current_process->next;
        } while (current_process != head);
    }

    ~round_robin_scheduler()
    {
        if (head)
        {
            process *current = head->next;
            process *temp;
            while (current != head)
            {
                temp = current;
                current = current->next;
                delete temp;
            }
            delete head;
        }
    }
};
int main(int argc, const char **argv)
{
    round_robin_scheduler scheduler(2);
    scheduler.add_process(1, 0, 8);
    scheduler.add_process(2, 1, 4);
    scheduler.add_process(3, 2, 6);
    scheduler.calculate_time();
    scheduler.display();
    return 0;
}