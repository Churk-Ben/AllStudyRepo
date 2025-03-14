#include <iostream>
#include <algorithm>
using namespace std;

long long int cnt(long long int m, long long int n)
{
    if (m == 0 || n == 0)
        return 0;
    long long int side = min(m, n);
    return cnt(max(m - side, n), min(m - side, n)) + 1;
}

int main()
{
    long long int m, n;
    cin >> m >> n;
    cout << cnt(max(m, n), min(m, n)) << endl;
    return 0;
}
