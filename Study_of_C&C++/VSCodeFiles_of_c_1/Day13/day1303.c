#include <stdio.h>

int main()
{
    int a, b, c;
    while (scanf("%d%d%d", &a, &b, &c) != EOF)
    {
        if (a + b > c && a + c > b && b + c > a)
        {
            if (a == b || a == c || b == c)
            {
                if (a == b && b == c)
                {
                    printf("�ȱ�������\n");
                }
                else
                {
                    printf("����������\n");
                }
            }
            else if (a * a + b * b == c * c || a * a + c * c == b * b || c * c + b * b == a * a)
            {
                printf("ֱ��������\n");
            }
            else
            {
                printf("��ͨ������\n");
            }
        }
        else
        {
            printf("���ܹ���������\n");
        }
    }
}