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