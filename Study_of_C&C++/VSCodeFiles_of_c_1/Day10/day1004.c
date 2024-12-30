#include <stdio.h>

int main()
{
    int i = 1, j = 0, k = 0, n;
    while (1)
    {
        k += 1;
        if (k == 10)
        {
            j += 1;
            k = 0;
        }
        if (j == 10)
        {
            i += 1;
            j = 0;
        }
        n = 100 * i + 10 * j + k;

        if (n == i * i * i + j * j * j + k * k * k)
        {
            printf("%d\n", n);
        }
        if (i == 9 && j == 9 && k == 9)
        {
            break;
        }
    }

    return 0;
}