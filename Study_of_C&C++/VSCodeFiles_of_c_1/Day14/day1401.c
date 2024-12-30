#include <stdio.h> //Ñ°Â··¨

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        // int i = 1, j = 1, t = 1;
        int a[n - 1][n - 1], map[n + 1][n + 1];
        for (int temp1 = 0; temp1 <= n + 1; temp1++)
        {
            for (int temp2 = 0; temp2 <= n + 1; temp2++)
            {
                map[temp1][temp2] = 0;
            }
        }
        for (int temp1 = 0; temp1 <= n + 1; temp1++)
        {
            map[temp1][0] = 1;
            map[temp1][n + 1] = 1;
            map[0][temp1] = 1;
            map[n + 1][temp1] = 1;
        }

        // while (1)
        // {
        //     while (map[i][j + 1] == 0)
        //     {
        //         map[i][j] = 1;
        //         a[i - 1][j - 1] = t++;
        //         j++;
        //     }

        //     while (map[i + 1][j] == 0)
        //     {
        //         map[i][j] = 1;
        //         a[i - 1][j - 1] = t++;
        //         i++;
        //     }

        //     while (map[i][j - 1] == 0)
        //     {
        //         map[i][j] = 1;
        //         a[i - 1][j - 1] = t++;
        //         j--;
        //     }

        //     while (map[i - 1][j] == 0)
        //     {
        //         map[i][j] = 1;
        //         a[i - 1][j - 1] = t++;
        //         i--;
        //     }

        //     if (t == n * n)
        //         break;
        // }

        for (int temp1 = 0; temp1 <= n + 1; temp1++)
        {
            for (int temp2 = 0; temp2 <= n + 1; temp2++)
            {
                printf("%4d ", map[temp1][temp2]);
            }
            printf("\n\n");
        }
        printf("\n");

        // for (int temp1 = 0; temp1 <= n - 1; temp1++)
        // {
        //     for (int temp2 = 0; temp2 <= n - 1; temp2++)
        //     {
        //         printf("%3d ", a[temp1][temp2]);
        //     }
        //     printf("\n");
        // }
    }

    return 0;
}