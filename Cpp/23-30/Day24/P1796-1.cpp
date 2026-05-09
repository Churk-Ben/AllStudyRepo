#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int solve(int m, int n) {
  if (m < 0 || n < 0) {
    return 0;
  }
  if ((m == 2 && n == 3) || (m == 3 && n == 2)) {
    return 1;
  } else {
    return solve(m - 2, n - 1) + solve(m - 1, n - 2);
  }
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