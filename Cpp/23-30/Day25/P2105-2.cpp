#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, V;
  cin >> n >> V;
  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i];

  int left = 0, sum = 0, ans = 0;
  for (int right = 0; right < n; ++right) {
    sum += a[right];
    while (sum > V) {
      sum -= a[left];
      left++;
    }
    ans = max(ans, sum);
  }
  cout << ans << endl;
  return 0;
}