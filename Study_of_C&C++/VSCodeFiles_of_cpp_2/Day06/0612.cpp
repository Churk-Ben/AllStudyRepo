#include <iostream>
using namespace std;

int func(int n)
{
    if (n == 1)
        return 1;
    return 2 * func(n - 1) + 2;
}

int main()
{
    int n;
    while (cin >> n)
    {
        cout << func(n) << endl;
    }
    return 0;
}
