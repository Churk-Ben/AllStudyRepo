#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

template <typename T> T read() {
  T x;
  cin >> x;
  return x;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string str = read<string>();
  if (str == "EMPTY") {
    str = "";
  }

  list<char> l(str.begin(), str.end());
  auto it = l.begin();

  int N = read<int>();

  while (N--) {
    switch (read<char>()) {
    case '<':
      if (it != l.begin())
        it--;
      break;
    case '>':
      if (it != l.end())
        it++;
      break;
    case 'I':
      l.insert(it, read<char>());
      break;
    case 'D':
      if (it != l.begin())
        it = l.erase(--it);
      break;
    }
  }

  for (auto c : l) {
    cout << c;
  }

  return 0;
}