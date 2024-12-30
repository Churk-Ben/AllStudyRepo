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
    int n, a, b, c;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d %d %d", &a, &b, &c);
        printf("%d\n", gcd(gcd(a, b),c));
        //printf("%d\n", lcm(a, b));
    }

    return 0;
}