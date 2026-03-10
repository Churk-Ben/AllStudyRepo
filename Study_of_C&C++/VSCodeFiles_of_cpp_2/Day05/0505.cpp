#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string add(string a, string b)
{
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    int m = max(a.size(), b.size());
    while (a.size() < m)
        a += '0';
    while (b.size() < m)
        b += '0';

    string ans;
    int cnt = 0;

    for (int i = 0; i < m; i++)
    {
        int n1 = a[i] - '0';
        int n2 = b[i] - '0';
        int sum = n1 + n2 + cnt;

        cnt = sum / 10;
        ans += (sum % 10) + '0';
    }

    if (cnt > 0)
    {
        ans += cnt + '0';
    }

    reverse(ans.begin(), ans.end());

    while (ans.size() > 1 && ans[0] == '0')
    {
        ans.erase(ans.begin());
    }

    return ans;
}

int main()
{
    string a, b;
    cin >> a >> b;
    cout << add(a, b) << endl;

    return 0;
}
