#pragma GCC optimize("Ofast")
#include <iostream>
#include <stack>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  int h[N + 1];
  stack<int> s, res;

  for (size_t i = 1; i <= (size_t)N; i++) {
    cin >> h[i];
  }

  for (size_t i = N; i > 0; i--) {

    while (!s.empty() && h[s.top()] <= h[i]) {
      s.pop();
    }
    if (s.empty()) {
      res.push(0);
    } else {
      res.push(s.top());
    }
    s.push(i);
  }

  for (size_t i = 0; i < (size_t)N; i++) {
    cout << res.top() << " ";
    res.pop();
  }

  return 0;
}