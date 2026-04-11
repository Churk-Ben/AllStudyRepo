#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  bool started = false;
  int left = 0, right = n;
  int mid;
  int feedback;

  cin >> n;

  while (true) {
    mid = (left + right) / 2;
    cout << "? " << mid << endl;
    cout.flush();

    cin >> feedback;
    switch (feedback) {
    case '<':
      right = mid;
      break;
    case '>':
      left = mid + 1;
      break;
    case '=':
      if (!started) {
        started = true;
        continue;
      }
      goto end;
    }
  }
end:
  cout << "! " << mid << endl;
  cout.flush();
  return 0;
}
