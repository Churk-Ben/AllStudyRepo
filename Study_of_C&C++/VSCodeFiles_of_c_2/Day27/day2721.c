#include <stdio.h>

int main()
{
    char str[500];
    fgets(str, 500, stdin);
    int p = 0, pmax, pmin, lmax = 0, lmin = 20;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == ' ')
        {
            if (i - p < lmin)
            {
                lmin = i - p;
                pmin = p;
            }
            if (i - p > lmax)
            {
                lmax = i - p;
                pmax = p;
            }
            p = i + 1;
        }

    for (int t = 0; t < lmax; t++)
        printf("%c", str[pmax + t]);
    printf("\0\n");
    for (int t = 0; t < lmin; t++)
        printf("%c", str[pmin + t]);
    printf("\0\n");

    return 0;
}