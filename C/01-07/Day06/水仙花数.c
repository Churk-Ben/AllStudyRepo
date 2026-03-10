#include <stdio.h>

int main()
{
    int i, j;
    for (i = 100; i <= 999; i++)
    {
        j = ((i / 100) * (i / 100) * (i / 100)) + ((i % 10) * (i % 10) * (i % 10)) + ((i / 10 % 10) * (i / 10 % 10) * (i / 10 % 10));
        if (i == j)
        {
            printf("%d\n", i);
        }
    }
    return 0;
}