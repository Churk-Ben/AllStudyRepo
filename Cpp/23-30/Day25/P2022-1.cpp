#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int a[N], b[N];
int m, n;

bool check(ll D) {
  int j = 0;
  for (int i = 0; i < m; i++) {
    while (j < n && b[j] < a[i] - D)
      j++;
    if (j == n || b[j] > a[i] + D)
      return false;
  }
  j = 0;
  for (int i = 0; i < n; i++) {
    while (j < m && a[j] < b[i] - D)
      j++;
    if (j == m || a[j] > b[i] + D)
      return false;
  }
  return true;
}

int main() {
  cin >> m >> n;
  for (int i = 0; i < m; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  sort(a, a + m);
  sort(b, b + n);
  ll l = 0, r = 1e9;
  while (l < r) {
    ll mid = (l + r) >> 1;
    if (check(mid))
      r = mid;
    else
      l = mid + 1;
  }
  cout << l << endl;
  return 0;
}