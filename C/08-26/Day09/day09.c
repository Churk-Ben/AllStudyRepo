#include <stdio.h>

int factorial(int m)
{
    if (m == 0)
        return 1;
    else
        return m * factorial(m - 1);
}

int main()
{
    int n;
    long int sum;
    while (scanf("%d", &n) != EOF)
    {
        sum = 0;
        for (int i = 0; i <= n; i++)
        {
            sum += factorial(i);
        }
        printf("%ld\n", sum);
    }
    return 0;
}
