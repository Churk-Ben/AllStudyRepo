#pragma GCC optimize("Ofast")
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  //   begin

  int n;
  cin >> n;
  vector<pair<int, int>> cows(n);
  for (int i = 0; i < n; i++) {
    cin >> cows[i].first >> cows[i].second;
  }

  sort(cows.begin(), cows.end());

  priority_queue<int, vector<int>, greater<int>> pq;
  for (auto &cow : cows) {
    if (!pq.empty() && pq.top() < cow.first) {
      pq.pop();
    }
    pq.push(cow.second);
  }
  cout << pq.size() << endl;

  //   end

  return 0;
}