// This program calculates the factorial of a number using the multiplication method.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int num1[10001], num2[10001];

string mulhighprecision(string s1, string s2)
{
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    int len1 = s1.size();
    int len2 = s2.size();
    vector<int> ans(len1 + len2 + 1, 0);
    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            ans[j + i] = ans[j + i] + (s1[i] - '0') * (s2[j] - '0');
            ans[j + i + 1] += (ans[j + i] / 10);
            ans[j + i] %= 10;
        }
    }
    vector<char> res;
    int cnt = 0;
    for (int i = ans.size() - 1; i >= 0; i--)
    {
        if (ans[i] != 0)
        {
            cnt = i;
            break;
        }
    }
    for (int i = cnt; i >= 0; i--)
    {
        res.push_back(ans[i] + '0');
    }
    res.push_back('\0');
    string resStr(res.data());
    return resStr;
}

int main()
{
    int num;
    cin >> num;
    string ans = "1";
    while (num > 0)
    {
        string s1 = to_string(num);
        string ans_r = mulhighprecision(ans, s1);
        ans = ans_r;
        num--;
    }
    cout << ans;
    return 0;
}