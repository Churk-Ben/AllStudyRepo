#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, ans = 0;
  cin >> N;
  vector<int> v(N);
  v.assign(N, 0);
  N -= 1;
  while (N--) {
    int a, b;
    cin >> a >> b;
    v[a - 1] += 1;
    v[b - 1] += 1;
  }
  for (size_t i = 1; i < v.size(); i++) {
    ans += (v[i] == 1);
  }
  cout << ans << endl;
  return 0;
}