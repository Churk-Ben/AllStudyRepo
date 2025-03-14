#include <iostream>
using namespace std;

int transform(int n, int B)
{
    int t = 0;
    int x = 1;
    while (n)
    {
        t += x * (n % 10);
        x *= B;
        n /= 10;
    }
    return t;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int p, q, r;
        cin >> p >> q >> r;
        int tp, tq, tr;
        for (int B = 3; B < 16; B++)
        {
            tp = transform(p, B);
            tq = transform(q, B);
            tr = transform(r, B);
            if (tp * tq == tr)
            {
                cout << B << endl;
                break;
            }
            if (B == 15 && tp * tq != tr)
            {
                cout << 0 << endl;
            }
        }
    }
    return 0;
}
