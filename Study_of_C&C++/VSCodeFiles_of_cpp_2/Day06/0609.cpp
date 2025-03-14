#include <iostream>
using namespace std;

long long int cnt(long long int m, long long int n)
{
    if (m == 0 || n == 0)
        return 0;
    long long int count = 0;
    while (m != 0 && n != 0)
    {
        long long int side = min(m, n);
        count += m / side * (n / side);
        m %= side;
        swap(m, n);
    }
    return count;
}

int main()
{
    long long int m, n;
    cin >> m >> n;
    cout << cnt(max(m, n), min(m, n)) << endl;
    return 0;
}
