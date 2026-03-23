#include <queue>
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  //   begin
  int n;
  cin >> n;
  vector<int> a(n), sum(n);
  priority_queue<int> pq;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sum[0] = a[0];
  for (int i = 1; i < n; i++) {
    sum[i] = sum[i - 1] + a[i];
    if (sum[i] < 0) {
      sum[i] = 0;
    }
    pq.push(sum[i]);
  }

  //   end
  cout << pq.top() << "\n";

  return 0;
}