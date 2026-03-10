#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

// 将字符串逆序存储到数组中
vector<int> adjust(string x)
{
    vector<int> res;
    for (int i = x.size() - 1; i >= 0; i--)
        res.push_back(x[i] - '0');
    return res;
}

// 高精度乘法
string mul(string a, string b, int scale)
{
    vector<int> A, B;
    vector<char> C;
    A = adjust(a);
    B = adjust(b);
    vector<int> res(A.size() + B.size(), 0);
    for (int i = 0; i < (int)A.size(); i++)
    {
        for (int j = 0; j < (int)B.size(); j++)
        {
            res[i + j] += A[i] * B[j];
            res[i + j + 1] += res[i + j] / scale;
            res[i + j] %= scale;
        }
    }
    for (int i = (int)res.size() - 1; i >= 0; i--)
        C.push_back((char)(res[i] % scale) + '0');
    reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == '0')
        C.pop_back();
    reverse(C.begin(), C.end());
    return string(C.begin(), C.end());
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
            ans = mul(ans, base, 10);
        base = mul(base, base, 10);
        n = n / 2;
    }
    ans.back() -= 1;
    reverse(ans.begin(), ans.end());
    int res[500];
    for (int i = 0; i < 500; i++)
    {
        if (i < (int)ans.size())
            res[499 - i] = ans[i] - '0';
        else
            res[499 - i] = 0;
    }
    for (int u : res)
        cout << u;
    return 0;
} // 最后一个测试点超时