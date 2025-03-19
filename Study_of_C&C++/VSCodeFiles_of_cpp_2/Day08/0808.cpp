#include <iostream>
#include <vector>
using namespace std;

int cnt = 0;
vector<bool> row(64, false);
vector<bool> col(64, false);
vector<bool> lDiag(64, false);
vector<bool> rDiag(64, false);

void dfs(int n)
{
    if (n == 8)
    {
        cnt++;
        return;
    }
    if (row[n])
    {
        dfs(n + 1);
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        if (!col[i] && !lDiag[32 + n - i] && !rDiag[n + i])
        {
            col[i] = true;
            lDiag[32 + n - i] = true;
            rDiag[n + i] = true;
            dfs(n + 1);
            col[i] = false;
            lDiag[32 + n - i] = false;
            rDiag[n + i] = false;
        }
    }
}

int main()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int temp;
            cin >> temp;
            if (temp == 1)
            {
                row[i] = true;
                col[j] = true;
                lDiag[32 + i - j] = true;
                rDiag[i + j] = true;
            }
        }
    }
    dfs(0);
    cout << cnt;
    return 0;
}
