#include <iostream>
#include <string>
using namespace std;

class process
{
    public:
    int burst_time,cb,arrival_time,index,waiting_time,turn_around_time;
};
void print(int n,process a[])
{
    for(int i=0;i<n;i++)
        cout<<"ID:"<<a[i].index<<"|Burst:"<<a[i].burst_time<<"|Arrival:"<<a[i].arrival_time<<endl;
}

int length(int n, process p[])
{
    int l=0;
    for(int i=0;i<n;i++)
        if(p[i].burst_time>0)
            l++;
    return l;
}

int main()
{
    int n;
    cout<<"Number of Processes :";
    cin>>n;
    process processes[n];
    //----------------------------------------input
    for(int i=0;i<n;i++)
    {
        cout<<"Job "<<i+1<<endl;
        cout<<"Burst Time = ";
        cin>>processes[i].burst_time;
        processes[i].cb = processes[i].burst_time;
        cout<<"Arrival Time = ";
        cin>>processes[i].arrival_time;
        processes[i].index=i+1;
    }
    cout<<"======================================\nProcesses before sorting\n"<<endl;
    print(n,processes);
    //--------------------------------------sorting according to the arrival times
    for(int i=0;i<n;i++)
    for(int j=0;j<n-1;j++)
    if(processes[j].arrival_time>processes[j+1].arrival_time)
    {
        process temp = processes[j];
        processes[j]=processes[j+1];
        processes[j+1]=temp;
    }
    cout<<"======================================\nProcesses after sorting\n"<<endl;
    print(n,processes);

    //---------------------------------------declaration of arrays to store the processes execution to print 
    int time = processes[0].arrival_time,current_process = 0;
    bool idel_state = false;
    int count=1,times[100]={processes[0].arrival_time},ids[100]={};
    //---------------------------------------simulation for each second
    while(length(n,processes)>0)
    {
        if(time>=processes[current_process].arrival_time)
        {
            if(idel_state)
            {
                times[count]=time;
                count++;
            }
            idel_state=false;
            processes[current_process].waiting_time = time - processes[current_process].arrival_time;
            time+=processes[current_process].burst_time;
            processes[current_process].turn_around_time = time - processes[current_process].arrival_time;
            processes[current_process].burst_time=0;
            ids[count]=processes[current_process].index;
            times[count]=time;
            current_process+=1;
            count++;
        }
        else
        {
            time++;
            idel_state=true;
        }
    }
    //--------------------------------------printing of the collected data
    cout<<"======================================\nGantt Chart\n"<<endl;
    cout<<"+";
    for(int i=1;i<count;i++)
    cout<<"--------+";
    cout<<endl<<"|";
    for(int i=1;i<count;i++)
    {
        cout.width(8);
        if(ids[i]==0)
            cout<<std::left<<"Idle"<<"|";
        else
            cout<<std::left<<"P"+to_string(ids[i])<<"|";
    }
    cout<<endl<<"+";
    for(int i=1;i<count;i++)
        cout<<"--------+";
    cout<<endl;
    for(int i=0;i<count;i++)
    {
        cout.width(9);
        cout<<std::left<<times[i];
    }
    cout << endl<<endl;
    cout<<"======================================\nTable\n"<<endl;
    cout << "Process ID |";
    cout << "Process Burst_time |";
    cout << "Process Arrival_time |";
    cout << "Process Waiting_time |";
    cout << "Process Turn_around_time"<<endl;
    cout.width(100);
    cout.fill('-');
    cout << " "<<endl;
    cout.fill(' ');
    int avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n;i++)
    {
        cout.width(11);
        cout<<std::left<<"P"+to_string(processes[i].index)<<"|";
        cout.width(19);
        cout << std::left << processes[i].cb << "|";
        cout.width(21);
        cout << std::left << processes[i].arrival_time << "|";
        cout.width(21);
        cout << std::left << processes[i].waiting_time << "|";
        cout.width(25);
        cout << std::left << processes[i].turn_around_time << endl;
        avg_wt += processes[i].waiting_time;
        avg_tat += processes[i].turn_around_time;
    }
    cout.width(100);
    cout.fill('-');
    cout << " "<<endl;
    cout.fill(' ');
    cout << "Average Turn Around Time = " << avg_tat << "| Average Waiting Time = "<< avg_wt<<endl;
}
 

