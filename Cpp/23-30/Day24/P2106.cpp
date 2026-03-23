#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

void spread(int x, int y, int hp, int n, const vector<vector<int>> &damage,
            const vector<vector<bool>> &wall, vector<vector<int>> &best) {
  if (x < 1 || x > n || y < 1 || y > n || wall[x][y]) {
    return;
  }
  if (hp <= 0 || hp <= best[x][y]) {
    return;
  }
  best[x][y] = hp;
  spread(x - 1, y, hp + damage[x - 1][y], n, damage, wall, best);
  spread(x + 1, y, hp + damage[x + 1][y], n, damage, wall, best);
  spread(x, y - 1, hp + damage[x][y - 1], n, damage, wall, best);
  spread(x, y + 1, hp + damage[x][y + 1], n, damage, wall, best);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k, x, y, hp;
  cin >> n >> k >> x >> y >> hp;

  vector<vector<int>> damage(n + 2, vector<int>(n + 2, 0));
  vector<vector<bool>> wall(n + 2, vector<bool>(n + 2, false));

  while (k--) {
    int a, b;
    cin >> a >> b;
    wall[a][b] = true;
    damage[a - 1][b] = -1;
    damage[a][b - 1] = -1;
    damage[a + 1][b] = -1;
    damage[a][b + 1] = -1;
  }

  vector<vector<int>> best(n + 2, vector<int>(n + 2, 0));
  spread(x, y, hp, n, damage, wall, best);

  int ans = 0;
  for (auto &row : best) {
    for (auto value : row) {
      if (value > 0) {
        ans++;
      }
    }
  }

  cout << ans << endl;

  return 0;
}
