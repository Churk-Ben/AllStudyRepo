#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool is_palindrome(const string &s);
bool is_palindrome_ignore_case(const string &s);
int main()
{
    using namespace std;
    string s;
    // 多组输入，直到按下Ctrl+Z结束测试
    while (cin >> s)
    {
        cout << boolalpha << "区分大小写: " << is_palindrome(s) << "\n"
             << "不区分大小写: " << is_palindrome_ignore_case(s) << "\n\n";
    }
}
bool is_palindrome(const string &s)
{
    for (int i = 0; i < s.size() / 2; i++)
    {
        if (s[i] != s[s.size() - i - 1])
            return false;
    }
    return true;
}
bool is_palindrome_ignore_case(const string &s)
{
    string s1;
    for (auto c : s)
        s1 += toupper(c);
    return is_palindrome(s1);
}