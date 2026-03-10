// This program is to multiply two numbers using high precision multiplication.
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int num1[10001];
int num2[10001];
int ans[100001];

void mulhighprecision(string s1, string s2)
{
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    int len1 = s1.size();
    int len2 = s2.size();
    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            ans[j + i] = ans[j + i] + (s1[i] - '0') * (s2[j] - '0');
            ans[j + i + 1] += (ans[j + i] / 10);
            ans[j + i] %= 10;
        }
    }
}

int main()
{
    string s1;
    string s2;
    cin >> s1;
    cin >> s2;
    mulhighprecision(s1, s2);
    int cnt = 0;
    for (int i = 10001; i >= 0; i--)
    {
        if (ans[i] != 0)
        {
            cnt = i;
            break;
        }
    }
    for (int i = cnt; i >= 0; i--)
    {
        cout << ans[i];
    }
    return 0;
}