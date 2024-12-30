#include <stdio.h>

void print_charman(int n);

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);
    print_charman(n); // 函数调用

    return 0;
}

// 函数print_charman定义
void print_charman(int n)
{
    int t = 0;
    for (int i = n; i >= 1; i--)
    {
        for (int j = 0; j < t; j++)
            printf("\t");
        for (int j = 0; j < 2 * i - 1; j++)
            printf(" o\t");
        printf("\n");
        for (int j = 0; j < t; j++)
            printf("\t");
        for (int j = 0; j < 2 * i - 1; j++)
            printf("<H>\t");
        printf("\n");
        for (int j = 0; j < t; j++)
            printf("\t");
        for (int j = 0; j < 2 * i - 1; j++)
            printf("I I\t");
        printf("\n");

        t++;
    }
}