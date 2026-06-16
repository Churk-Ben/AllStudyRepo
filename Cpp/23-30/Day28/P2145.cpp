#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;

    if (b < a) {
        cout << 0 << '\n';
        return 0;
    }

    long long diff = b - a;
    vector<long long> dp(diff + 1);
    dp[0] = 1;

    for (long long i = 1; i <= diff; ++i) {
        if (i >= 2) {
            dp[i] += dp[i - 2];
        }
        if (i >= 3) {
            dp[i] += dp[i - 3];
        }
    }

    cout << dp[diff] << '\n';
    return 0;
}
