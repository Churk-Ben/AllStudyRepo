#include <stdio.h>

int main()
{
    double c, f;

    while (scanf_s("%lf", &c) != EOF)
    {
        printf("请输入摄氏度: ");

        f = (c * 9.0 / 5.0) + 32;

        printf("%.2f摄氏度 = %.2f华氏度\n", c, f);
    }

    return 0;
}
