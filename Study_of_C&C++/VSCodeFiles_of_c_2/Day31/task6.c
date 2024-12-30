#include <stdio.h>
#include <string.h>
#define N 5

int check_id(char *str); // ��������

int main()
{
    char *pid[N] = {"31010120000721656X",
                    "3301061996X0203301",
                    "53010220051126571",
                    "510104199211197977",
                    "53010220051126133Y"};
    int i;

    for (i = 0; i < N; ++i)
        if (check_id(pid[i])) // ��������
            printf("%s\tTrue\n", pid[i]);
        else
            printf("%s\tFalse\n", pid[i]);

    return 0;
}

// ��������
// ����: ���ָ��strָ������֤���봮��ʽ���Ƿ�Ϸ�
// ��ʽ�Ϸ�������1�����򣬷���0

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