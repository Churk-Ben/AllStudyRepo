#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int lknum = rand() % 30 + 1;
    int n = 3,input;
    printf("猜猜2024年11月哪一天会是你的lucky day\n开始咯，你有三次机会，猜吧（1~30）：");
    while (n--)
    {
        scanf("%d", &input);
        if (input == lknum)
        {
            printf("哇，猜中了:)");
            break;
        }
        else if (input < lknum)
        {
            printf("你猜的日期早了，你的lucky day还没到呢\n");
            if (n==0)
            {
                printf("你已经用完了三次机会啦，偷偷告诉你，lucky day是%d号哦\n",lknum);
                break;
            }
            else
            {
                printf("再猜（1~30）：");
                continue;
            }
        }
        else
        {
            printf("你猜的日期晚了，你的lucky day在前面哦\n");
            if (n==0)
            {
                printf("你已经用完了三次机会啦，偷偷告诉你，lucky day是%d号哦\n",lknum);
                break;
            }
            else
            {
                printf("再猜（1~30）：");
                continue;
            }
        }
    }
}
