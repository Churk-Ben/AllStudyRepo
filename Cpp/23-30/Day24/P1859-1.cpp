#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> words;
vector<int> used;
int max_len = 0;

int get_overlap(const string &a, const string &b) {
  return a.substr(a.length() - 1) == b.substr(0, 1);
}

void dfs(string current_word, int current_len) {
  max_len = max(max_len, current_len);
  for (int i = 0; i < n; ++i) {
    if (used[i] < 2) {
      int overlap = get_overlap(current_word, words[i]);
      if (overlap > 0) {
        used[i]++;
        dfs(words[i], current_len + words[i].length() - overlap);
        used[i]--;
      }
    }
  }
}

int main() {
  cin >> n;
  words.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> words[i];
  }
  char start_char;
  cin >> start_char;

  used.assign(n, 0);

  for (int i = 0; i < n; ++i) {
    if (words[i][0] == start_char) {
      used[i]++;
      dfs(words[i], words[i].length());
      used[i]--;
    }
  }

  cout << max_len << endl;
  return 0;
}
