#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    int n, m;
    queue<int> q;
    cin >> n >> m;
    vector<int> a;
    for (int i = 0; i < n; i++)
    {
        q.push(i + 1);
    }
    int cnt = 0;
    while (!q.empty())
    {
        cnt++;
        if (cnt == m)
        {
            a.push_back(q.front());
            q.pop();
            cnt = 0;
        }
        else
        {
            int x = q.front();
            q.pop();
            q.push(x);
        }
    }
    for (int u : a)
    {
        cout << u << " ";
    }
}