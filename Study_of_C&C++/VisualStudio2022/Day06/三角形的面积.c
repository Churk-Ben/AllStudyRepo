#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, c, s, area;
    while (scanf("%lf %lf %lf", &a, &b, &c) != EOF)
    {
        if ((a + b > c) && (a + c > b) && (b + c > a))
        {
            s = (a + b + c) / 2.0;

            area = sqrt(s * (s - a) * (s - b) * (s - c));

            printf("%.2f\n", area);
        }
        else
        {
            printf("-1\n");
        }
    }

    return 0;
}