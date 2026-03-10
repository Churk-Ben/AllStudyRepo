#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    map<string, string> mp;
    mp["0000"] = "0";
    mp["0001"] = "1";
    mp["0010"] = "2";
    mp["0011"] = "3";
    mp["0100"] = "4";
    mp["0101"] = "5";
    mp["0110"] = "6";
    mp["0111"] = "7";
    mp["1000"] = "8";
    mp["1001"] = "9";
    mp["1010"] = "A";
    mp["1011"] = "B";
    mp["1100"] = "C";
    mp["1101"] = "D";
    mp["1110"] = "E";
    mp["1111"] = "F";
    string a, u = "";
    cin >> a;
    if (a.length() % 4 != 0)
    {
        a.insert(0, 4 - a.length() % 4, '0');
    }
    for (int i = 0; i < a.length(); i += 4)
    {
        u.append(mp[a.substr(i, 4)]);
    }
    cout << u << endl;

    return 0;
}
