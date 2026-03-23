#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int C(int n, int m) {
  if (m == 0 || m == n) {
    return 1;
  }
  return C(n - 1, m - 1) + C(n - 1, m);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  int garbage[n];
  for (int i = 0; i < n; i++) {
    cin >> garbage[i];
  }

  cout << C(n, m) << endl;

  return 0;
}