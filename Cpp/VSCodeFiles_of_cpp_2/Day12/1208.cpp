#include <iostream>
#include <string>
#include <algorithm>
std::string dec2n(int x, int n = 2);
int main()
{
    int x;
    while (std::cin >> x)
    {
        std::cout << "十进制: " << x << '\n'
                  << "二进制: " << dec2n(x) << '\n'
                  << "八进制: " << dec2n(x, 8) << '\n'
                  << "十二进制: " << dec2n(x, 12) << '\n'
                  << "十六进制: " << dec2n(x, 16) << '\n'
                  << "三十二进制: " << dec2n(x, 32) << "\n\n";
    }
}

std::string dec2n(int x, int n)
{
    if (x == 0)
        return "0";
    std::string s;
    while (x > 0)
    {
        int r = x % n;
        s += (r < 10) ? ('0' + r) : ('A' + r - 10);
        x /= n;
    }
    reverse(s.begin(), s.end());
    return s;
}