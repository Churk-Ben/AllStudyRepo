#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

bool check(int limit, const vector<int> &A, const vector<int> &B) {
  for (int a : A) {
    auto it = lower_bound(B.begin(), B.end(), a - limit);
    if (it == B.end() || *it > a + limit) {
      return false;
    }
  }
  for (int b : B) {
    auto it = lower_bound(A.begin(), A.end(), b - limit);
    if (it == A.end() || *it > b + limit) {
      return false;
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int M, N;
  cin >> M >> N;
  vector<int> A(M), B(N);
  for (int i = 0; i < M; ++i)
    cin >> A[i];
  for (int i = 0; i < N; ++i)
    cin >> B[i];

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  int left = 0, right = 1e6;
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (check(mid, A, B)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  cout << left << endl;
  return 0;
}