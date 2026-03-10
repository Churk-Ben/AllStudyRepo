#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int gender[50];
    char name[50][20];
    int isUsed[50] = {0};
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &gender[i]);
        scanf("%s", name[i]);
    }

    for (int i = 0; i < n; i++)
    {
        if (isUsed[i])
        {
            continue;
        }

        for (int j = n - 1; j >= 0; j--)
        {
            if (i != j && !isUsed[j] && gender[i] != gender[j])
            {
                printf("%s %s\n", name[i], name[j]);
                isUsed[i] = 1;
                isUsed[j] = 1;
                break;
            }
        }
    }

    return 0;
}