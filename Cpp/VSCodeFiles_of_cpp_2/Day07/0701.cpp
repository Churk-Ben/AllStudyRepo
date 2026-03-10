#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int find(const vector<int> &arr, double target)
{
    int res = arr[0];
    double diff = abs(target - res);

    for (int i = 1; i < (int)arr.size(); ++i)
    {
        double temp = abs(target - arr[i]);
        if (temp < diff)
        {
            diff = temp;
            res = arr[i];
        }
    }

    return res;
}

int main()
{
    int l, n;
    cin >> l >> n;
    vector<int> ants(n);
    for (int i = 0; i < n; i++)
        cin >> ants[i];
    sort(ants.begin(), ants.end());

    vector<int> t(4);

    t = {
        l - ants[0],
        ants[n - 1],
        find(ants, l / 2.0),
        l - find(ants, l / 2.0)};

    sort(t.begin(), t.end());
    cout << t[0] << " " << t[3] << endl;
    return 0;
}
