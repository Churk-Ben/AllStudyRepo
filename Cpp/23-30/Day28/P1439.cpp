#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int W;
  cin >> W;
  int n;
  cin >> n;
  vector<pair<int, int>> item(n);
  for (int i = 0; i < n; i++) {
    int w, v;
    cin >> w >> v;
    item[i] = {w, v};
  }

  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= W; j++) {
      if (j < item[i - 1].first) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = max(dp[i - 1][j],
                       dp[i - 1][j - item[i - 1].first] + item[i - 1].second);
      }
    }
  }
  cout << dp[n][W] << endl;

  return 0;
}