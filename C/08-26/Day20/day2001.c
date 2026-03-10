#include <stdio.h>

int isprime(int n)
{
    if (n < 2)
        return 0;
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int cnt = 0;
    for (int i = 1; i < 101; i += 2)
    {
        if (isprime(i)&&isprime(i + 2))
        {
                printf("%d %d\n", i, i + 2);
                cnt++;
        }
    }
    printf("Total cnt: %d\n", cnt);
    return 0;
}
