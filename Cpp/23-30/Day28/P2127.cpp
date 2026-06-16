#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int u, v, weight;
  Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
  bool operator<(const Edge &other) const {
    return weight > other.weight; // 降序，最大生成树
  }
};

class DSU {
  vector<int> parent, rank;

public:
  DSU(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++)
      parent[i] = i;
  }

  int find(int x) {
    if (parent[x] != x)
      parent[x] = find(parent[x]);
    return parent[x];
  }

  bool unite(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry)
      return false;
    if (rank[rx] < rank[ry])
      parent[rx] = ry;
    else if (rank[rx] > rank[ry])
      parent[ry] = rx;
    else {
      parent[ry] = rx;
      rank[rx]++;
    }
    return true;
  }
};

int maxSpanningTreeKruskal(int n, vector<Edge> &edges) {
  sort(edges.begin(), edges.end()); // 按权重降序排序
  DSU dsu(n);
  int totalWeight = 0;
  int edgesUsed = 0;

  for (const Edge &e : edges) {
    if (dsu.unite(e.u, e.v)) {
      totalWeight += e.weight;
      edgesUsed++;
      if (edgesUsed == n - 1)
        break;
    }
  }

  return edgesUsed == n - 1 ? totalWeight : -1; // -1表示无法生成树
}

// 示例
int main() {
  int n;
  cin >> n;
  vector<Edge> edges;
  int m;
  cin >> m;
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back(Edge(u, v, w));
  }

  int result = maxSpanningTreeKruskal(n, edges);
  cout << result << endl;
  return 0;
}