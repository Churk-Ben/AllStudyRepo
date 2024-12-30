#include <stdio.h>

int main()
{
    int a, b;
    int i, j;
    while (scanf("%d%d", &a, &b) != EOF)
    {
        i = a;
        j = b;
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        b = i * j / a;
        printf("%d\n%d\n", a, b);
    }

    return 0;
}