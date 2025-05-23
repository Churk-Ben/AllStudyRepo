# LevOJ平台.sln
> 苯蒟蒻也没系统学过算法，群佬有更高级的算法一定要在评论区贴一下喵~
## P1034 字符串的循环移位
### 问题描述
![alt text](image.png)
### 解决方法
```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    string temp1 = s.substr(0, n);
    string temp2 = s.substr(n, s.length() - 1);
    string result = temp2 + temp1;
    cout << result << endl;
    return 0;
}
```
## P1042 手机短号
### 问题描述
![alt text](image-1.png)
### 解决方法
```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string phnumber;
    cin >> phnumber;
    cout << "6" << phnumber.substr(6, 10) << endl;
    return 0;
}
```
## P1118 ISBN号
### 问题描述
![alt text](image-2.png)
### 解决方法
```cpp
#include <iostream>
using namespace std;

char map[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'X'};

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        string isbn;
        cin >> isbn;
        int sum = 0;
        int pos = 1;
        for (int i = 0; i < 11; i++)
        {
            if (isbn[i] == '-')
            {
                continue;
            }
            sum += (isbn[i] - '0') * pos;
            pos++;
        }
        if (isbn[12] == map[sum % 11])
        {
            cout << "Right" << endl;
        }
        else
        {
            cout << isbn.substr(0, 12) + map[sum % 11] << endl;
        }
    }

    return 0;
}

```
## P1169 乒乓球
### 问题描述
![alt text](image-4.png)
### 解决方法
```cpp
#include <iostream>
#include <string>
using namespace std;
void judge(string t, int rule)
{
    int a = 0, b = 0;
    for (int i = 0; i < (int)t.size() - 1; i++)
    {
        if (t[i] == 'E')
            break;
        if (t[i] == 'W')
            a++;
        else if (t[i] == 'L')
            b++;
        if ((a >= rule && a - b > 1) || (b >= rule && b - a > 1))
        {
            cout << a << ":" << b << endl;
            a = 0, b = 0;
        }
    }
    cout << a << ":" << b << endl
         << endl;
}

int main()
{
    string t;
    getline(cin, t);
    judge(t, 11);
    judge(t, 21);
    return 0;
}

```
## P1202 字符串插入
### 问题描述
![alt text](image-5.png)
### 解决方法
```cpp
#include <iostream>
#include <string>
using namespace std;

string func(const string &str, const string &substr)
{
    char maxChar = 0;
    size_t maxCharIndex = 0;

    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] > maxChar)
        {
            maxChar = str[i];
            maxCharIndex = i;
        }
    }

    string result = str.substr(0, maxCharIndex + 1) + substr + str.substr(maxCharIndex + 1);
    return result;
}

int main()
{
    string str;
    string substr;
    cin >> str >> substr;
    string result = func(str, substr);
    cout << result << endl;

    return 0;
}

```
## P1226 数字合并
### 问题描述
![alt text](image-6.png)
### 解决方法
```cpp
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

bool compare(const string &a, const string &b)
{
    return a + b > b + a;
}

string func(vector<string> &nums)
{
    sort(nums.begin(), nums.end(), compare);
    string ans;
    for (string s : nums)
        ans += s;
    return ans;
}

int main()
{
    int n;
    cin >> n;
    vector<string> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];
    string ans = func(nums);
    cout << ans << endl;
    return 0;
}

```
## P2026 国王的演讲
### 问题描述
![alt text](image-7.png)
### 解决方法
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main()
{
    map<char, string> mp;
    string temp;
    int m, n;

    cin >> n;
    while (n--)
    {
        cin >> temp;
        mp[temp[0]] = temp;
    }

    cin >> m;
    vector<string> str(m);
    for (int i = 0; i < m; i++)
    {
        cin >> str[i];
        str[i] = mp[str[i][0]];
    }

    for (int i = 0; i < m; i++)
    {
        cout << str[i] << " ";
    }
    cout << endl;

    return 0;
}

```

## P1131 子串
### 问题描述
![alt text](image-3.png)
### 解决方法
```cpp
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

```


> 注 ：
> 
> P1325 区间合并、P2045 数字蚯蚓已在LevOJ.sln-3中

# 第五期完结!
__看完点个赞再走嘛__