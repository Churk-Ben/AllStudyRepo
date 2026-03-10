#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int l, n;
    cin >> l >> n;
    vector<int> ants(n);
    for (int i = 0; i < n; i++)
        cin >> ants[i];
    sort(ants.begin(), ants.end());
    vector<int> t(4);
    if (n % 2)
    {
        t = {
            l - ants[0],
            ants[n - 1],
        };
    }
    sort(t.begin(), t.end());
    cout << t[0] << t[3] << endl;
    return 0;
}
// unfinished