#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

int main()
{
    int a, b, c;
    double del, x1, x2;
    while (1)
    {
        printf("��������ϵ��: ");
        scanf("%d %d %d", &a, &b, &c);
        if (a == 0)
        {
            if (b == 0 && c == 0)
            {
                break;
            }
            else
            {
                printf("����һ����Ч�Ķ��η��̣�\n");
                continue;
            }
        }

        del = b * b - 4 * a * c;

        if (del > 0)
        {
            x1 = (-b + sqrt(del)) / (2 * a);
            x2 = (-b - sqrt(del)) / (2 * a);
            printf("�������������ȵ�ʵ����\n");
            printf("x1 = %.2lf\n", x1);
            printf("x2 = %.2lf\n", x2);
            continue;
        }
        else if (del == 0)
        {
            x1 = (-b) / (2 * a);
            printf("������������ȵ�ʵ����\n");
            printf("x1 = x2 = %.2lf\n", x1);
            continue;
        }
        else if (del < 0)
        {
            double real, imag;
            real = -b / (2 * a);
            imag = sqrt(-del) / (2 * a);
            printf("������������������\n");
            printf("x1 = %.2lf+%.2lfi\n", real, imag);
            printf("x2 = %.2lf-%.2lfi\n", real, imag);
            continue;
        }
    }
    return 0;
}