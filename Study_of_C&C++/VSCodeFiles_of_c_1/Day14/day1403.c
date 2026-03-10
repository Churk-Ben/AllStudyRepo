#include <stdio.h>//Àı–°±ﬂΩÁ∑®ÃÓ≥‰æÿ’Û

void fillMatrix(int n)
{
    int matrix[n][n];
    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    int t = 1;

    while (t <= n * n)
    {
        for (int i = left; i <= right; i++)
        {
            matrix[top][i] = t++;
        }
        top++;

        for (int i = top; i <= bottom; i++)
        {
            matrix[i][right] = t++;
        }
        right--;

        if (top <= bottom)
        {
            for (int i = right; i >= left; i--)
            {
                matrix[bottom][i] = t++;
            }
            bottom--;
        }

        if (left <= right)
        {
            for (int i = bottom; i >= top; i--)
            {
                matrix[i][left] = t++;
            }
            left++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        fillMatrix(n);
    }

    return 0;
}