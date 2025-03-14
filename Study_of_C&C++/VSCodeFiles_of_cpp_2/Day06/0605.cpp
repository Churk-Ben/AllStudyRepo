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
