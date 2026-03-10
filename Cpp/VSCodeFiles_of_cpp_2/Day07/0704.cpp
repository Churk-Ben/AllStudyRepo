#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> num(n);
    vector<list<int>> door(n);
    int t;
    for (int i = 0; i < n; i++)
    {
        cin >> t;
        num[i] = t;
    }
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < num[i]; j++)
        {
            int x;
            cin >> x;
            door[i].push_back(x);
        }
    }

    int m, r, q;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> r >> q;
        door[q - 1].push_front(r);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j : door[i])
        {
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}