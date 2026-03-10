#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **p;
    int i, j;
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};

    p = (int **)malloc(2 * sizeof(int *));
    for (i = 0; i < 2; i++)
    {
        p[i] = (int *)malloc(3 * sizeof(int));
        for (j = 0; j < 3; j++)
        {
            p[i][j] = arr[i][j];
        }
    }

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < 2; i++)
    {
        free(p[i]);
    }
    free(p);

    return 0;
}