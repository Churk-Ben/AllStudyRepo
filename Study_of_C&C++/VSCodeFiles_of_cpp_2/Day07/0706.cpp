#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    string num1, num2;
    vector<char> num3;
    cin >> num1 >> num2;
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    int len1 = num1.length();
    int len2 = num2.length();
    for (int i = 0; i < len2; i++)
        num3.push_back(num2[i]);

    int n = len1 - len2;
    while (n--)
        num3.push_back('0');

    vector<int> ans(len1);
    for (int i = 0; i < len1; i++)
    {
        ans[i] = ans[i] + num1[i] - num3[i];
        if (ans[i] < 0 && i + 1 < len1)
        {
            ans[i] += 10;
            ans[i + 1] -= 1;
        }
    }
    reverse(ans.begin(), ans.end());
    int cnt = 0;
    for (int i = 0; i < len1; i++)
    {
        if (ans[i] != 0)
        {
            cnt = i;
            break;
        }
    }
    for (int i = cnt; i < len1; i++)
    {
        cout << ans[i];
    }
    return 0;
}