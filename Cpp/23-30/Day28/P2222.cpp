#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> children(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        children[u].push_back(v);
    }

    vector<int> depth(n + 1, -1);
    queue<int> q;
    depth[1] = 0;
    q.push(1);

    int ans = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        ans = max(ans, depth[u]);
        for (int v : children[u])
        {
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }
    cout << ans << "\n";
    return 0;
}

