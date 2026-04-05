#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void bin_search(ll x, ll y, ll target) {
  int is_odd = (x + y) % 2;
  ll mid = is_odd ? (x + y - 1) / 2 : (x + y) / 2;
  if (mid == target) {
    cout << "G";
    return;
  }
  if (mid > target) {
    cout << "L";
    bin_search(x, mid - 1, target);
  } else {
    cout << "R";
    bin_search(mid + 1, y, target);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll x, y, target;
  cin >> x >> y >> target;
  bin_search(x, y, target);
  return 0;
}