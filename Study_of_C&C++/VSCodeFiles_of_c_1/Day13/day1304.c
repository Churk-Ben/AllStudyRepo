#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int lknum = rand() % 30 + 1;
    int n = 3,input;
    printf("�²�2024��11����һ��������lucky day\n��ʼ�����������λ��ᣬ�°ɣ�1~30����");
    while (n--)
    {
        scanf("%d", &input);
        if (input == lknum)
        {
            printf("�ۣ�������:)");
            break;
        }
        else if (input < lknum)
        {
            printf("��µ��������ˣ����lucky day��û����\n");
            if (n==0)
            {
                printf("���Ѿ����������λ�������͵͵�����㣬lucky day��%d��Ŷ\n",lknum);
                break;
            }
            else
            {
                printf("�ٲ£�1~30����");
                continue;
            }
        }
        else
        {
            printf("��µ��������ˣ����lucky day��ǰ��Ŷ\n");
            if (n==0)
            {
                printf("���Ѿ����������λ�������͵͵�����㣬lucky day��%d��Ŷ\n",lknum);
                break;
            }
            else
            {
                printf("�ٲ£�1~30����");
                continue;
            }
        }
    }
}
