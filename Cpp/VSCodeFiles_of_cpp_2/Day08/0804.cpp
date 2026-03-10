#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void solve(long n, long t)
{
    vector<long> a(n);
    long sum = 0;
    for (long i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    for (long i = 0; i < n; i++)
    {
        sum += a[i];
        if (sum > t)
        {
            cout << i << endl;
            return;
        }
        else if (sum == t)
        {
            cout << i + 1 << endl;
            return;
        }
    }
    cout << n << endl;
}

int main()
{
    long n, t;
    while (cin >> n >> t)
    {
        solve(n, t);
    }
    return 0;
}
