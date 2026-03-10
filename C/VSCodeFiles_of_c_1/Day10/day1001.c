#include <stdio.h>
int gcd(int a, int b)
{
    if (a % b == 0)
    {
        return b;
    }
    else
    {
        return gcd(b, a % b);
    }
}

int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}

int main()
{
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF)
    {
        printf("%d\n", gcd(a, b));
        printf("%d\n", lcm(a, b));
    }

    return 0;
}