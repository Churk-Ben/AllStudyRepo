#include <iostream>
using namespace std;
int cnt = 0;
bool hang[64];
bool lie[64];
bool zuoxiexian[64];
bool youxiexian[64];
void dfs(int n)
{
    if (n == 8)
    {
        cnt++;
        return;
    }
    if (hang[n])
    {
        dfs(n + 1);
    }
    for (int i = 0; i < 8; i++)
    {

        if (!lie[i] && !zuoxiexian[32 + n - i] && !youxiexian[n + i])
        {
            lie[i] = true;
            zuoxiexian[32 + n - i] = true;
            youxiexian[n + i] = true;
            dfs(n + 1);
            lie[i] = false;
            zuoxiexian[32 + n - i] = false;
            youxiexian[n + i] = false;
        }
    }
}
int main()
{
    for (int i = 0; i < 64; i++)
    {
        hang[i] = false;
        lie[i] = false;
        zuoxiexian[i] = false;
        youxiexian[i] = false;
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int temp;
            cin >> temp;
            if (temp == 1)
            {
                hang[i] = true;
                lie[j] = true;
                zuoxiexian[32 + i - j] = true;
                youxiexian[i + j] = true;
            }
        }
    }
    dfs(0);
    cout << cnt;
    return 0;
}