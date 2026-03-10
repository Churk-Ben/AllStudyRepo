#include <algorithm>
#include <iostream>
#include <vector>


using namespace std;

int main() {
  int N, M, Q;
  cin >> N >> M >> Q;
  int u, v, k;
  vector<int> map[N + 1];
  for (int i = 0; i < M; i++) {
    cin >> u >> v;
    map[u].push_back(v);
  }
  for (int i = 0; i < Q; i++) {
    cin >> u >> k;
    if (map[u].size() < (size_t)k) {
      cout << -1 << endl;
    } else {
      sort(map[u].begin(), map[u].end());
      cout << map[u][k - 1] << endl;
    }
  }
  return 0;
}