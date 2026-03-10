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