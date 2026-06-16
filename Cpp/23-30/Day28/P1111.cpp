#include <iostream>
#include <vector>
using namespace std;

int n, k, m;
vector<vector<int>> adj;
vector<int> color;
long long ans = 0;

void dfs(int u)
{
    if (u > n)
    {
        ans++;
        return;
    }
    for (int c = 1; c <= m; ++c)
    {
        bool ok = true;
        for (int v : adj[u])
        {
            if (color[v] == c)
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            color[u] = c;
            dfs(u + 1);
            color[u] = 0;
        }
    }
}

int main()
{
    cin >> n >> k >> m;
    adj.assign(n + 1, {});
    color.assign(n + 1, 0);

    for (int i = 0; i < k; ++i)
    {
        int u, v;
        cin >> u >> v;
        if (u == v)
            continue;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    cout << ans << endl;
    return 0;
}
