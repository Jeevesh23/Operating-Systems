#include<bits/stdc++.h>
using namespace std;

class Process
{
	public:
	static int count;
	char id;
	int at , bt , ct , tat , wt , orig_bt;


	Process()
	{
    	cin >> this -> at >> this -> bt;
    	this -> id = 'A' + count++ ;
    	this -> orig_bt = this -> bt ;
	}
};
int Process :: count = 0;

bool cmp(Process &a , Process &b)
{
	if(a.at == b.at)
    	return a.bt < b.bt;
	return a.at < b.at ;
}

void display(vector<Process> &p , vector<pair<char , int >> & gantte)
{    
	int n = p.size();
	int m  = gantte.size();
	cout<<"\nGantte Chart : \n";
	for(int i = 0 ; i < m ; i++)
	{
    	cout<<left<<setw(6)<<"|"<<gantte[i].first<<" 	";
	}
	cout<<"|"<<endl;
	cout<<"        	";
	for(int i = 0 ; i < m ; i++)
	{
    	cout << left << setw(12) << gantte[i].second;
	}
	cout<<endl<<endl;


	sort(p.begin() , p.end() , [&](Process a , Process b){return a.id < b.id;});
	float avg_wt = 0 , avg_tat = 0;
	cout<<left<<setw(20)<<"Process Id"<<setw(20)<<"Arrival Time"<<setw(20)<<"Burst Time"<<setw(20)<<"Completion Time"<<setw(20)<<"Turn Around Time"<<setw(20)<<"Waiting Time"<<endl;
	for(int i = 0 ; i < n ; i++)
	{
    	cout<<setw(20)<<p[i].id<<setw(20)<<p[i].at<<setw(20)<<p[i].bt<<setw(20)<<p[i].ct<<setw(20)<<p[i].tat<<setw(20)<<p[i].wt<<endl;
    	avg_wt += p[i].wt;
    	avg_tat += p[i].tat;
	}
	avg_tat /= n ;
	avg_wt /= n ;
	cout<<"Avg_WT : "<<avg_wt<<endl;
	cout<<"Avg_TAT : "<<avg_tat<<endl;
}

void RoundRobin(vector<Process>& p , int TQ)
{
	int n = p.size();
	sort(p.begin() , p.end() , cmp);

	queue<Process> q;
	vector<Process> ans;
	vector<pair<char,int>> gantte;
	int index = 0 , start = p[index].at;
	q.push(p[index++]);

	while( !q.empty() or index < n )
	{
    	Process curr  = q.front() ; q.pop() ;
    	int temp_bt = curr.bt;
    	if(curr.bt <= TQ)
    	{
        	curr.ct = start + curr.bt;
        	curr.tat = curr.ct - curr.at;
        	curr.wt = curr.tat - curr.orig_bt;

        	start = start + curr.bt;

        	curr.bt = curr.orig_bt;
        	gantte.push_back({curr.id , curr.ct});
        	ans.push_back(curr);
    	}
    	else
    	{
        	curr.ct = start + TQ;
        	curr.bt = curr.bt - TQ;

        	gantte.push_back({curr.id, curr.ct});
        	start = start + TQ;
    	}
    	while(  index < n and p[index].at <= start )
    	{
        	q.push(p[index]);
        	index++;
    	}
    	if(temp_bt > TQ)
        	q.push(curr);

    	if(q.empty() and index < n and p[index].at > start )
        	start = p[index].at;
	}   
	display(ans , gantte);
}

int main()
{
	int n , TQ;
	cout<<"Enter the Number of Processes and Time Quantum\n";
	cin>> n >> TQ;

	cout<<"Enter the Arrival Time and Burst Time Of Each Process\n";
	vector<Process> p(n);

	RoundRobin(p , TQ);

	return 0;
}