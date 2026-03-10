#include <iostream>
using namespace std;
int cnt = 0;
bool row[64];
bool col[64];
bool leftLine[64];
bool rightLine[64];
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
    }
    for (int i = 0; i < 8; i++)
    {

        if (!col[i] && !leftLine[32 + n - i] && !rightLine[n + i])
        {
            col[i] = true;
            leftLine[32 + n - i] = true;
            rightLine[n + i] = true;
            dfs(n + 1);
            col[i] = false;
            leftLine[32 + n - i] = false;
            rightLine[n + i] = false;
        }
    }
}
int main()
{
    for (int i = 0; i < 64; i++)
    {
        row[i] = false;
        col[i] = false;
        leftLine[i] = false;
        rightLine[i] = false;
    }
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
                leftLine[32 + i - j] = true;
                rightLine[i + j] = true;
            }
        }
    }
    dfs(0);
    cout << cnt;
    return 0;
}