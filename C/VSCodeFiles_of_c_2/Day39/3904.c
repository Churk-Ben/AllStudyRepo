#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    if (n == 0)
    {
        printf("0\n");
        return 0;
    }
    int binary[32];
    int i = 0;
    while (n > 0)
    {
        binary[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%d", binary[j]);
    }
    printf("\n");
    return 0;
}