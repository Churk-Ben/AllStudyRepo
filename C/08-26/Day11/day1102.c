#include <stdio.h>

int main()
{
    int n, m, N, a1, a2, b1, b2, sum, i = 0, j = 0;
    scanf("%d%d", &n, &m);
    scanf("%d", &N);
    for (int t = 0; t < N; t++)
    {
        scanf("%d%d%d%d", &a1, &a2, &b1, &b2);
        sum = a1 + b1;
        if (a2 == b2)
        {
            continue;
        }
        if (a2 == sum)
        {
            i++;
            if (i > n)
            {
                printf("A\n");
                printf("%d", j);
                break;
            }
        }
        if (b2 == sum)
        {
            j++;
            if (j > m)
            {
                printf("B\n");
                printf("%d", i);
                break;
            }
        }
    }
    return 0;
}