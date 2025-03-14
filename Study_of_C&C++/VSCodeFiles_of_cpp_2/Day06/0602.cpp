#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string match(string str1, string str2)
{
    int m = str1.size();
    int n = str2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int mLen = 0;
    int end = 0;

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > mLen)
                {
                    mLen = dp[i][j];
                    end = i;
                }
            }
        }
    }

    string res = (mLen > 0) ? str1.substr(end - mLen, mLen) : "";
    return res;
}

int main()
{
    int n;
    cin >> n;
    string str0;
    cin >> str0;
    n--;

    while (n--)
    {
        string str1;
        cin >> str1;
        string strFor = match(str0, str1);
        reverse(str1.begin(), str1.end());
        string strRev = match(str0, str1);
        if (strFor.size() >= strRev.size())
            str0 = strFor;
        else
            str0 = strRev;
    }

    cout << (str0.empty() ? 0 : str0.size()) << endl;
    return 0;
}
