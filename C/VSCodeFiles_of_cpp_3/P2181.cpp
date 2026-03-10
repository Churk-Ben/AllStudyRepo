#pragma GCC optimize("Ofast")
#include <iostream>
#include <queue>

using namespace std;

int main() {
  // Optimize I/O operations
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, K, op, x;
  priority_queue<long> q;

  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    cin >> op >> x;
    switch (op) {
    case 1:
      if (q.size() < (size_t)K) {
        q.push(x);
      } else if (q.top() > x) {
        q.pop();
        q.push(x);
      }
      break;

    case 2:
      if (q.size() < (size_t)K) {
        cout << -1 << "\n";
      } else {
        cout << q.top() << "\n";
      }
      break;
    }
  }
  return 0;
}