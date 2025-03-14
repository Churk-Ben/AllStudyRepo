#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

string highprecisionmultiply(string s1, string s2)
{
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    int len1 = s1.size();
    int len2 = s2.size();
    vector<int> ans(10001);
    for (int i = 0; i < 501; i++)
    {
        if (i < len1)
            for (int j = 0; j < 501; j++)
            {
                if (j < len2)
                {
                    ans[j + i] = ans[j + i] + (s1[i] - '0') * (s2[j] - '0');
                    ans[j + i + 1] += (ans[j + i] / 10);
                    ans[j + i] %= 10;
                }
            }
    }
    vector<char> res;
    while (ans.size() > 1 && ans.back() == 0)
    {
        ans.pop_back();
    }
    for (int i = ans.size() - 1; i >= 0; i--)
    {
        res.push_back(ans[i] + '0');
    }
    res.push_back('\0');
    string resStr(res.data());
    return resStr;
}
int main()
{
    int n;
    cin >> n;
    string base = "2";
    string ans = "1";
    while (n > 0)
    {
        if (n % 2 == 1)
        {
            ans = highprecisionmultiply(ans, base);
        }
        base = highprecisionmultiply(base, base);
        n = n / 2;
    }
    ans[ans.size() - 1] -= 1;
    reverse(ans.begin(), ans.end());
    int result[500];
    int len = ans.size();
    for (int i = 0; i < 500; i++)
    {
        if (i < len)
            result[499 - i] = ans[i] - '0';
        else
            result[499 - i] = 0;
    }
    for (int u : result)
    {
        cout << u;
    }
    return 0;
}