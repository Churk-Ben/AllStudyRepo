#include <stdio.h>

int main()
{
    int n, m, s, map[100][100] = {0};
    scanf("%d%d%d", &n, &m, &s);
    int rc, ind, cnt = 0;
    for (int i = 0; i < s; i++)
    {
        scanf("%d%d", &rc, &ind);
        switch (rc)
        {
        case 0:
            for (int i = 0; i < m; i++)
            {
                map[ind - 1][i] = 1;
            }
            break;
        case 1:
            for (int i = 0; i < n; i++)
            {
                map[i][ind - 1] = 1;
            }
            break;

        default:
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] == 0)
            {
                cnt++;
            }
        }
    }
    printf("%d", cnt);
    return 0;
}
