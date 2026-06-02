#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string a, b;
  cin >> a >> b;

  int n = a.size();
  int m = b.size();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1));
  for (int i = 0; i <= n; ++i)
    dp[i][0] = i;
  for (int j = 0; j <= m; ++j)
    dp[0][j] = j;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
      dp[i][j] =
          min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
    }
  }

  cout << dp[n][m] << endl;
  return 0;
}
