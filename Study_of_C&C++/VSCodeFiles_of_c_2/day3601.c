#include <stdio.h>

double fun(int n)
{
    double s = 0;
    int i, j, t;
    for (t = 1; t <= n; t++)
    {
        int a = 1, b = 1;
        for (i = 1; i <= t; i++)
            a *= i;
        for (j = 1; j <= t; j++)
            b *= (2 * j + 1);
        s += (double)a / b;
    }

    return s;
}

int main()
{
    int n;
    double result;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    result = fun(n);

    printf("The value of the sum is: %f", result);

    return 0;
}