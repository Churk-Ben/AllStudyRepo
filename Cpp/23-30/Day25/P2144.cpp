#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  unordered_map<char, int> map;
  string s;
  cin >> s;
  for (char c : s) {
    map[c]++;
  }

  while (q--) {
    char c;
    cin >> c;
    cout << map[c] << '\n';
  }
  return 0;
}