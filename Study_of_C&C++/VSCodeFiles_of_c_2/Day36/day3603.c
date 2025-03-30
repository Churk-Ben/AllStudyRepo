#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    double x;
    double y;
    printf("x:");
    scanf("%lf", &x);
    if (x < 2 && x >= x)
    {
        y = x;
    }
    else if (x >= 2 && x < 4)
    {
        y = 2 * x - 2;
    }
    else
    {
        y = 3 * x - 6;
    }
    printf("y:%.6lf\n", y);
    system("pause");
    return 0;
}