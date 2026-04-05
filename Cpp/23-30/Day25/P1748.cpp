#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> A(n), B(n), C(n), D(n);
    for (int i = 0; i < n; ++i) {
      cin >> A[i] >> B[i] >> C[i] >> D[i];
    }
    unordered_map<int, int> sumAB;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        sumAB[A[i] + B[j]]++;
      }
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int sumCD = C[i] + D[j];
        if (sumAB.count(-sumCD)) {
          ans += sumAB[-sumCD];
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}