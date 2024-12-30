#include <stdio.h>
#include <math.h>
int main()
{
    int n;
    long int a;
    double b;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%ld", &a);
        b = sqrt(a);
        if ((int)b == b)
        {
            printf("%d\n", (int)b);
            break;
        }
    }

    return 0;
}