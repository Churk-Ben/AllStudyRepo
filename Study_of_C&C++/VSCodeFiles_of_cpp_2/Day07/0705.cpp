#include <iostream>
#include <string>
using namespace std;

int num1[10001], num2[10001], ans[10001];
string s1, s2;

int main()
{
    cin >> s1 >> s2;
    int len1 = s1.length();
    for (int i = 0; i < len1; i++)
        num1[i] = s1[len1 - 1 - i] - '0';
    int len2 = s2.length();
    for (int i = 0; i < len2; i++)
        num2[i] = s2[len2 - 1 - i] - '0';

    for (int i = 0; i < max(len1, len2); i++)
    {
        ans[i] = num1[i] + num2[i] + ans[i];
        if (ans[i] >= 10)
        {
            ans[i] %= 10;
            ans[i + 1]++;
        }
    }
    int cnt = 0;
    for (int i = 10000; i >= 0; i--)
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
