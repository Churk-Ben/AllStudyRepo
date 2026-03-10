#include <stdio.h>

int main()
{
    int i, cnt;
    for (i = 100, cnt = 0; i <= 200; ++i)
    {
        if (i % 3)
        {
            printf("%6d", i);
            if (++cnt % 6 == 0)
            {
                printf("\n");
            }
        }
    }
    if (cnt % 6)
    {
        printf("\n");
    }
    return 0;
}