#pragma GCC optimize("Ofast")
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> Game;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  //   begin
  int m, n, res;
  while (cin >> m >> n) {
    res = m;
    vector<Game> a(n);
    vector<int> tag(n + 10, 0);
    // t, w
    for (int i = 0; i < n; i++) {
      cin >> a[i].first;
    }
    for (int i = 0; i < n; i++) {
      cin >> a[i].second;
    }

    sort(a.begin(), a.end(),
         [](Game a, Game b) { return a.second > b.second; });

    for (int i = 0; i < n; i++) {
      int pos = -1;
      for (int j = a[i].first; j >= 1; j--) {
        if (tag[j] == 0) {
          tag[j] = 1;
          pos = j;
          break;
        }
      }
      if (pos == -1) {
        res -= a[i].second;
      }
    }

    cout << res << endl;

    //   end
  }
  return 0;
}