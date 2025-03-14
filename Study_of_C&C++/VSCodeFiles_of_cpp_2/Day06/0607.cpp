#include <iostream>
#define M 150
#define N 150
using namespace std;

int main()
{
    int m, n;
    int a[M][N];
    int Case = 0;
    while (true)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                a[i][j] = 0;
            }
        }
        m = 0, n = 0;
        cin >> m >> n;
        if (m == 0 && n == 0)
        {
            break;
        }
        Case++;
        for (int x = 0; x < 3; x++)
        {
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    int t;
                    cin >> t;
                    a[i][j] += t;
                }
            }
        }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                a[i][j] = a[i][j] / 3;
            }
        }
        cout << "Case " << Case << ":" << endl;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << a[i][j];
                if (j != n - 1)
                    cout << ",";
            }
            cout << endl;
        }
    }
    return 0;
}