#include <stdio.h>

void print_charman(int n);

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);
    print_charman(n); // ��������

    return 0;
}

// ����print_charman����
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