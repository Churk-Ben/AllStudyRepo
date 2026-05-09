#pragma GCC optimize("Ofast")
#include <iostream>
#include <stack>

using namespace std;

int solve(int m, int n) {
  if (m < 0 || n < 0) {
    return 0;
  }
  int cnt = 0;
  stack<pair<int, int>> st;
  st.push({m, n});
  while (!st.empty()) {
    auto [x, y] = st.top();
    st.pop();
    if (x < 0 || y < 0) {
      continue;
    }
    if ((x == 2 && y == 3) || (x == 3 && y == 2)) {
      cnt++;
      continue;
    }
    st.push({x - 2, y - 1});
    st.push({x - 1, y - 2});
  }
  return cnt;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  //   begin
  int m, n, res = 0;
  cin >> m >> n;
  res = solve(m, n);
  cout << res << endl;
  //   end

  return 0;
}
