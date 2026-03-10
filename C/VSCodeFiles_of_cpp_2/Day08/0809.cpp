#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

// 大数加法
string add(const string &a, const string &b)
{
    string res;
    int carry = 0;
    int i = a.size() - 1, j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0)
    {
        int digit_a = i >= 0 ? a[i] - '0' : 0;
        int digit_b = j >= 0 ? b[j] - '0' : 0;
        int sum = digit_a + digit_b + carry;
        carry = sum / 10;
        res.push_back(sum % 10 + '0');
        i--;
        j--;
    }

    reverse(res.begin(), res.end());
    return res;
}

// 大数乘法
string mul(const string &a, const string &b)
{
    int len1 = a.size(), len2 = b.size();
    vector<int> ans(len1 + len2, 0);

    for (int i = 0; i < len1; i++)
    {
        int digit_a = a[len1 - 1 - i] - '0';
        for (int j = 0; j < len2; j++)
        {
            int digit_b = b[len2 - 1 - j] - '0';
            ans[i + j] += digit_a * digit_b;
            ans[i + j + 1] += ans[i + j] / 10;
            ans[i + j] %= 10;
        }
    }

    string res;
    for (int i = ans.size() - 1; i >= 0; i--)
    {
        if (ans[i] || res.size())
            res.push_back(ans[i] + '0');
    }

    return res.empty() ? "0" : res;
}

// 快速幂
string pow(const string &a, int b)
{
    string base = a;
    string res = "1";

    while (b > 0)
    {
        if (b % 2 == 1)
            res = mul(res, base);
        base = mul(base, base);
        b /= 2;
    }

    return res;
}

int main()
{
    int a, b;
    cin >> a >> b;
    string sum = "0";

    for (int i = 0; i < a; i++)
    {
        string a = to_string(i + 1);
        string ans = pow(a, b);
        sum = add(sum, ans);
    }

    if (sum.size() <= 4)
        cout << sum;
    else
        cout << sum.substr(sum.size() - 4);

    return 0;
}
