#include <stdio.h>

int main()
{
    int j = 0;
    for (int i = 100; i <= 200; i++)
    {
        if (i % 3 == 0)
        {
            continue;
        }
        j++;
        printf("%6d", i);
        if (j % 6 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");

    return 0;
}