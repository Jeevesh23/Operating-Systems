#include <iostream>
using namespace std;

class process
{
public:
    int burst_time, cbt, arrival_time, priority, index, turn_around_time, waiting_time;
};

int length(int n, process p[])
{
    int l = 0;
    for (int i = 0; i < n; i++)
        if (p[i].burst_time > 0)
            l++;
    return l;
}

int main()
{
    bool pre_def = false;
    // bool pre_def = true;
    int n = 4;
    if (!pre_def)
    {
        cout << "Number of Processes :";
        cin >> n;
    }
    int arrival[] = {8, 2, 1, 0};
    int burst[] = {1, 2, 1, 4};
    int priority[] = {1, 3, 2, 1};

    process processes[n];
    //-------------------------------------------------------------------input
    for (int i = 0; i < n; i++)
    {
        if (!pre_def)
        {
            cout << "Job " << i + 1 << endl;
            cout << "Burst Time = ";
            cin >> processes[i].burst_time;
            cout << "Arrival Time = ";
            cin >> processes[i].arrival_time;
            cout << "Priority = ";
            cin >> processes[i].priority;
            // processes[i].arrival_time = 0;
        }
        else
        {
            processes[i].burst_time = burst[i];
            processes[i].arrival_time = arrival[i];
            processes[i].priority = priority[i];
            // processes[i].arrival_time = 0;
        }
        processes[i].cbt = processes[i].burst_time;
        processes[i].index = i + 1;
    }

    // sort wrt arrival,priority
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
    }
    int count = 0;
    int time = processes[0].arrival_time;
    int times[100] = {time}, p_ids[100];

    while (length(n, processes) > 0)
    {
        // finding the next process to execute
        int p;
        bool idle = true;
        for (p = 0; p < n && processes[p].burst_time < 0; p++)
            ;
        for (int i = p; i < n; i++)
            if (processes[i].burst_time >= 0 && processes[i].arrival_time <= time && processes[i].priority <= processes[p].priority)
            {
                idle = false;
                if (processes[i].priority < processes[p].priority)
                    p = i;
            }
        if (idle)
        {
            int min = 9e8;
            for (int i = 0; i < n; i++)
                if (processes[i].arrival_time >= time && processes[i].arrival_time < min)
                    min = i;
            p_ids[count] = -1;
            time = processes[min].arrival_time;
        }
        else
        {
            p_ids[count] = p;
            processes[p].waiting_time = time - processes[p].arrival_time;
            time += processes[p].burst_time;
            processes[p].burst_time = -1;
            processes[p].turn_around_time = time - processes[p].arrival_time;
        }
        times[count + 1] = time;
        count++;
    }

    cout << "\n\nGantt Chart\n+";
    for (int i = 0; i < count; i++)
        cout << "-------+";
    cout << endl;
    cout << "|";
    for (int i = 0; i < count; i++)
    {
        cout.width(7);
        if (p_ids[i] != -1)
            cout << std::left << "P" + to_string(processes[p_ids[i]].index) << "|";
        else
            cout << std::left << "Idel"
                 << "|";
    }

    cout << "\n+";
    for (int i = 0; i < count; i++)
        cout << "-------+";
    cout << endl;

    for (int i = 0; i <= count; i++)
    {
        cout.width(8);
        cout << times[i];
    }
    cout << "\n\n\t\t\tAnalysis Table\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1; j++)
            if (processes[j].index > processes[j + 1].index)
            {
                process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }

    cout << "\nID | ARRIVAL TIME | PRIORITY | BURST TIME | WAITING TIME | TURN AROUND TIME |\n";
    cout.fill('-');
    cout.width(78);
    cout << std::right << " " << endl;
    cout.fill(' ');
    double avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++)
    {
        cout.width(2);
        cout << std::left << "P" + to_string(processes[i].index) << " | ";
        cout.width(12);
        cout << std::left << processes[i].arrival_time << " | ";
        cout.width(8);
        cout << std::left << processes[i].priority << " | ";
        cout.width(10);
        cout << std::left << processes[i].cbt << " | ";
        cout.width(12);
        cout << std::left << processes[i].waiting_time << " | ";
        cout.width(16);
        cout << std::left << processes[i].turn_around_time << " | ";
        cout << endl;
        avg_wt += processes[i].waiting_time;
        avg_tat += processes[i].turn_around_time;
    }
    cout << "\nAverage Waiting Time = " << avg_wt / n << " | Average Turn Around Time = " << avg_tat / n;
}