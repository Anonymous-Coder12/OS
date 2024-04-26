#include <iostream>
using namespace std;
int main()
{
    int n, i, j, pos, sum = 0, disk_size, start;
    cout << "Enter the size of disk: ";
    cin >> disk_size;
    cout << "Enter the starting position: ";
    cin >> start;
    cout << "Enter the number of requests: ";
    cin >> n;
    int a[n];
    cout << "Enter the requests: ";
    for (i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    for (i = 0; i < n; i++)
    {
        if (a[i] == start)
        {
            pos = i;
            break;
        }
    }
    for (i = pos; i < n; i++)
    {
        sum += abs(start - a[i]);
        start = a[i];
    }
    sum += abs(start - disk_size);
    start = 0;
    for (i = 0; i < pos; i++)
    {
        sum += abs(start - a[i]);
        start = a[i];
    }
    cout << "Total head movement: " << sum << endl;
    return 0;
}