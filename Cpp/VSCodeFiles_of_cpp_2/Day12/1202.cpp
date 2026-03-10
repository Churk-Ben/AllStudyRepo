#include <iostream>
using namespace std;

int main()
{
    int x, y, z;
    x = 1;
    y = 2;
    z = 3;
    x = y-- <= x || x + y != z;
    cout << x << "-" << y << "-" << z;
    return 0;
}