#include <iostream>
using namespace std;

int func(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    return func(n - 1) + func(n - 2);
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
