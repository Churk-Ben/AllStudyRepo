#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

int main()
{
    std::string s;
    std::string s1;
    for (char c = 'a'; c <= 'z'; c++)
    {
        s += c;
    }
    std::cout << right << std::setw(2) << " ";
    for (auto c : s)
    {
        std::cout << std::right << std::setw(2) << c;
        s1 += std::toupper(c);
    }
    cout << endl;
    for (int i = 1; i <= 26; i++)
    {
        std::cout << std::right << std::setw(2) << i;
        std::rotate(s1.begin(), s1.begin() + 1, s1.end());
        for (auto c : s1)
        {
            std::cout << std::right << std::setw(2) << c;
        }
        cout << endl;
    }
    return 0;
}