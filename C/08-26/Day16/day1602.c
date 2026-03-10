#include <stdio.h>

void func(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    printf("\n");
}

int main()
{
    int n;
    scanf("%d", &n);
    func(n);
    return 0;
}
