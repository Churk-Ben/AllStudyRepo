#include <stdio.h>

int main()
{
    double c, f;

    while (scanf_s("%lf", &c) != EOF)
    {
        printf("���������϶�: ");

        f = (c * 9.0 / 5.0) + 32;

        printf("%.2f���϶� = %.2f���϶�\n", c, f);
    }

    return 0;
}
