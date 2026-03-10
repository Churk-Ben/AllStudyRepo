#include <iostream>
using namespace std;

int func(int m, int n)
{
    if (m < n)
        return func(m, m);
    if (m == 0 || n == 1)
        return 1;
    return func(m - n, n) + func(m, n - 1);
}

int main()
{
    int m, n;
    while (cin >> m >> n)
    {
        cout << func(m, n) << endl;
    }
    return 0;
}
