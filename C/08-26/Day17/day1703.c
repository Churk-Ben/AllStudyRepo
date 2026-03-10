#include <stdio.h>

int func(int n)
{
    int ori = n;
    int rev = 0;

    while (n > 0)
    {
        int digit = n % 10;
        rev = rev * 10 + digit;
        n /= 10;
    }

    return ori == rev;
}

int main()
{
    int num;
    while (scanf("%d", &num) != EOF)
    {
        if (func(num))
        {
            printf("yes\n");
        }
        else
        {
            printf("no\n");
        }
    }

    return 0;
}
