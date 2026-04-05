#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  long long V, w, sum = 0, ans = 0;
  cin >> n >> V;
  set<long long> pre = {0};

  while (n--) {
    cin >> w;
    sum += w;
    auto it = pre.lower_bound(sum - V);
    if (it != pre.end())
      ans = max(ans, sum - *it);
    pre.insert(sum);
  }

  cout << ans << '\n';
  return 0;
}