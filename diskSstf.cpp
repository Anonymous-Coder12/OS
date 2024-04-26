#include <iostream>
#include <vector>
#include <map>
using namespace std;
int main()
{
    int i, j, k, n, m, sum = 0, x, y, h;
    cout << "Enter the size of disk\n";
    cin >> m;
    cout << "Enter number of requests\n";
    cin >> n;
    cout << "Enter the requests\n";
    vector<int> a(n), b;
    map<int, int> mp;
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
        mp[a[i]]++;
    }
    for (i = 0; i < n; i++)
    {
        if (a[i] > m)
        {
            cout << "Error, Unknown position " << a[i] << "\n";
            return 0;
        }
    }
    cout << "Enter the head position\n";
    cin >> h;
    int temp = h;
    int ele;
    b.push_back(h);
    int count = 0;
    while (count < n)
    {
        int diff = 999999;
        for (auto q : mp)
        {
            if (abs(q.first - temp) < diff)
            {
                ele = q.first;
                diff = abs(q.first - temp);
            }
        }
        mp[ele]--;
        if (mp[ele] == 0)
        {
            mp.erase(ele);
        }
        b.push_back(ele);
        temp = ele;
        count++;
    }
    cout << b[0];
    temp = b[0];
    for (i = 1; i < b.size(); i++)
    {
        cout << " -> " << b[i];
        sum += abs(b[i] - temp);
        temp = b[i];
    }
    cout << '\n';
    cout << "Total head movements = " << sum << '\n';
    cout << "Average head movement = " << (float)sum / n << '\n';
    return 0;
}