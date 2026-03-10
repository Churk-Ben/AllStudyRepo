#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    map<int, vector<int>> a;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        a[y].push_back(x);
    }
    for (int i = m; i >= 0; i--)
    {
        if (a.count(i))
        {
            cout << i << " ";
            for (int j = 0; j < (int)a[i].size(); j++)
            {
                cout << a[i][j] << " ";
            }
        }
        else
        {
            cout << i;
        }
        cout << endl;
    }
    return 0;
}