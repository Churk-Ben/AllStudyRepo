#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int bfs(int sx, int sy, int tx, int ty, int m, int n,
        vector<vector<int>> &map) {
  int dx[] = {-1, 1, 0, 0};
  int dy[] = {0, 0, -1, 1};

  queue<pair<pair<int, int>, int>> q;
  q.push({{sx, sy}, 0});
  map[sx][sy] = 1;

  while (!q.empty()) {
    auto curr = q.front();
    q.pop();

    int x = curr.first.first;
    int y = curr.first.second;
    int step = curr.second;

    if (x == tx && y == ty) {
      return step;
    }

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (nx >= 0 && nx < m && ny >= 0 && ny < n && map[nx][ny] == 0) {
        map[nx][ny] = 1;
        q.push({{nx, ny}, step + 1});
      }
    }
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  //   begin
  int m, n;
  cin >> m >> n;
  vector<vector<int>> map(m, vector<int>(n));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> map[i][j];
    }
  }
  int sx, sy, tx, ty;
  cin >> sx >> sy >> tx >> ty;

  sx--, sy--, tx--, ty--;

  int ans = bfs(sx, sy, tx, ty, m, n, map);
  cout << ans << "\n";

  //   end

  return 0;
}