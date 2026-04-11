#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  int left = 0, right = n;
  int mid;
  char feedback;
  while (feedback != '=') {
    mid = (left + right) / 2;
    cout << "? " << mid << endl;
    cout.flush();
    cin >> feedback;
    if (feedback == '<') {
      right = mid;
      continue;
    } else if (feedback == '>') {
      left = mid + 1;
      continue;
    }
  }
  return 0;
}
