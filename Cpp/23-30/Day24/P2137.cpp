#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

bool can_reach(int x, int y) {
  if (x == y) {
    return true;
  }
  if (x > y) {
    return false;
  }
  return can_reach(x * 2, y) || can_reach(x * 3, y);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  //   begin
  int N;
  cin >> N;

  while (N--) {
    int x, y;
    cin >> x >> y;
    if (can_reach(x, y)) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }

  //   end

  return 0;
}