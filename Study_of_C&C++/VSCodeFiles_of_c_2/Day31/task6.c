#include <stdio.h>
#include <string.h>
#define N 5

int check_id(char *str); // 函数声明

int main()
{
    char *pid[N] = {"31010120000721656X",
                    "3301061996X0203301",
                    "53010220051126571",
                    "510104199211197977",
                    "53010220051126133Y"};
    int i;

    for (i = 0; i < N; ++i)
        if (check_id(pid[i])) // 函数调用
            printf("%s\tTrue\n", pid[i]);
        else
            printf("%s\tFalse\n", pid[i]);

    return 0;
}

// 函数定义
// 功能: 检查指针str指向的身份证号码串形式上是否合法
// 形式合法，返回1，否则，返回0

int check_id(char *str)
{
    if (strlen(str) != 18)
        return 0;

    for (int i = 0; i < 17; i++)
        if (str[i] > '9')
            return 0;

    if ((str[17] <= '9' && str[17] >= '0') || str[17] == 'X')
        return 1;
    else
        return 0;
}