#include <stdio.h>

int main()
{
    int index[6][6] = {0};
    int n;
    for (int i = 0; i < 6; i++)
    {
        scanf("%d", &index[0][i]);
    }
    scanf("%d", &n);
    for (int i = 0; i < 6; i++)
    {
        int temp = 6;
        for (int j = 1; j <= 5;)
        {
            if (temp==index[0][i])
            {
                temp--;
            }
            else
            {
                index[j][i] = temp;
                temp--;
                j++;
            }
        }
    }
    for (int i = 0; i < 6; i++)
    {
        printf("%d ", index[n][i]);
    }
    printf("\n");
    return 0;
}
