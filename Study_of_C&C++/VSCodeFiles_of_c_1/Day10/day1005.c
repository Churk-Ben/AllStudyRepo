#include <stdio.h>

int main()
{
    int n, c;
    long long max = 2147483647, min = -2147483648, sum = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        printf("00%d",i);
        scanf("%d", &c);
        getchar();
        if (sum + c - max > 0 || sum + c - min < 0)
        {
            printf("%d\n", i);
            break;
        }
        sum += c;
        printf("01%d",i);
        if (i == n)
        {
            printf("0");
        }
    }

    return 0;
}