#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

void grow(priority_queue<int> &max_length, const vector<string> &S, char first,
          int length, bool started) {
  bool extended = false;
  for (size_t i = 0; i < S.size(); i++) {
    if (S[i].front() == first) {
      extended = true;
      vector<string> next = S;
      string current = next[i];
      next.erase(next.begin() + i);
      int add = started ? static_cast<int>(current.size()) - 1
                        : static_cast<int>(current.size());
      grow(max_length, next, current.back(), length + add, true);
    }
  }
  if (!extended) {
    max_length.push(length);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  //   begin
  int n;
  cin >> n;
  vector<string> S(2 * n);
  priority_queue<int> max_length;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    S[i * 2] = s;
    S[i * 2 + 1] = s;
  }
  char first;
  cin >> first;

  grow(max_length, S, first, 0, false);
  cout << max_length.top() << endl;

  //   end

  return 0;
}
