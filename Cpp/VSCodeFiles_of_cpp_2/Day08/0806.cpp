#include <string>
#include <algorithm> // reverse
#include <vector>
#include <iostream>
using namespace std;
string add(string a, string b)
{

    if (a.size() < b.size())
        swap(a, b);

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    string res;
    int carry = 0;

    for (int i = 0; i < a.size(); i++)
    {
        int digit_a = a[i] - '0';
        int digit_b = i < b.size() ? b[i] - '0' : 0;

        int sum = digit_a + digit_b + carry;
        carry = sum / 10;
        res.push_back(sum % 10 + '0');
    }

    // 处理最后的进位
    if (carry)
        res.push_back('1');

    reverse(res.begin(), res.end());

    // 去除前导零（如果结果不是"0"）
    while (res.size() > 1 && res[0] == '0')
        res.erase(res.begin());

    return res;
}
string highprecisionmultiply(string s1, string s2)
{
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    int len1 = s1.size();
    int len2 = s2.size();
    vector<int> ans(10001);
    for (int i = 0; i < 5; i++)
    {
        if (i < len1)
            for (int j = 0; j < 5; j++)
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
string kuaisumi(string dishu, int zhishu)
{
    string base = dishu;
    string ans = "1";
    while (zhishu > 0)
    {
        if (zhishu % 2 == 1)
        {
            ans = highprecisionmultiply(ans, base);
        }
        base = highprecisionmultiply(base, base);
        zhishu = zhishu / 2;
    }
    return ans;
}
int main()
{
    int a, b;
    cin >> a >> b;
    string sum = "0";
    for (int i = 1; i <= a; i++)
    {
        string dishu = to_string(i);
        string ans = kuaisumi(dishu, b);
        sum = add(sum, ans);
    }
    if (sum.size() <= 4)
    {
        cout << sum;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            cout << sum[sum.size() - 4 + i];
        }
    }
}