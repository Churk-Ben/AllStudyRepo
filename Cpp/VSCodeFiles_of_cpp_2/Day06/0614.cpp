#include <iostream>
using namespace std;

bool is_semi_prime(int n)
{
    if (n <= 3)
        return false;
    int cnt = 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            cnt++;
            if (cnt > 1)
                return false;
        }
    }
    if (cnt == 1)
        return true;
    else
        return false;
}

int main()
{
    int n;
    while (cin >> n)
    {
        if (is_semi_prime(n))
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
    return 0;
}
