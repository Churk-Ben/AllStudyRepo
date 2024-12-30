#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, c, s, area;
    while (1)
    {
        printf("输入三条边长: ");
        scanf_s("%lf %lf %lf", &a, &b, &c);

        if ((a == 0) && (b == 0) && (c == 0))
        {
            break;
        }

        if ((a + b > c) && (a + c > b) && (b + c > a))
        {
            s = (a + b + c) / 2.0;

            area = sqrt(s * (s - a) * (s - b) * (s - c));

            printf("三角形面积为: %.2f\n", area);
        }
        else
        {
            printf("无法构成三角形。\n");
        }
    }

    return 0;
}
