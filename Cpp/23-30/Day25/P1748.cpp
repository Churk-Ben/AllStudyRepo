#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    int A[2000], B[2000], C[2000], D[2000];
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
        int target = -(C[i] + D[j]);
        if (sumAB.count(target)) {
          ans += sumAB[target];
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}