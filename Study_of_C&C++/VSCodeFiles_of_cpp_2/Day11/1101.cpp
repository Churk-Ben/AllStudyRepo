#include <iostream>
using namespace std;

int main()
{
    int a{1};
    int &pa = a;
    pa = 10;
    cout << a << endl;
    cout << &a << endl;
    cout << pa << endl;
    cout << &pa << endl;
    return 0;
}