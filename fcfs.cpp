// C++ program for implementation of FCFS
// scheduling
#include <iostream>
#include <vector>
using namespace std;

void findavgTime(vector<pair<int, int> > &processes, int n, vector<pair<int, pair<int, int> > > &burst_time)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    int sum = 0;
    sum = sum + burst_time[0].first;
    for (int i = 0; i < n; i++)
    {
        sum = sum + burst_time[i].second.second;
        // p[i].ct = sum;
        tat[burst_time[i].second.first - 1] = sum - burst_time[i].first;
        wt[burst_time[i].second.first - 1] = tat[burst_time[i].second.first - 1] - burst_time[i].second.second;
        if (sum < burst_time[i + 1].first)
        {
            int t = burst_time[i + 1].first - sum;
            sum = sum + t;
        }
    }
    cout << "Processes "
         << " Burst time "
         << " Waiting time "
         << " Turn around time\n";

    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i + 1 << "\t\t" << burst_time[i].second.second << "\t "
             << wt[i] << "\t\t " << tat[i] << endl;
    }

    cout << "Average waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n;
}

// Driver code
int main()
{
    // process id's
    // int processes[] = {1, 2, 3};
    vector<pair<int, int> > processes(3);
    processes[0].first = 0;
    processes[0].second = 1;
    processes[1].first = 3;
    processes[1].second = 2;
    processes[2].first = 6;
    processes[2].second = 3;

    int n = sizeof processes / sizeof processes[0];

    // Burst time of all processes
    // int burst_time[] = {10, 5, 8};
    vector<pair<int, pair<int, int> > > burst_time(3);
    burst_time[0].first = 0;
    burst_time[0].second.first = 1;
    burst_time[0].second.second = 5;
    burst_time[1].first = 3;
    burst_time[1].second.first = 2;
    burst_time[1].second.second = 9;
    burst_time[2].first = 6;
    burst_time[2].second.first = 3;
    burst_time[2].second.second = 6;
    sort(processes.begin(), processes.end());
    sort(burst_time.begin(), burst_time.end());

    findavgTime(processes, n, burst_time);
    return 0;
}
