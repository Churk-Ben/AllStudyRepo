#include <stdio.h>
#include <math.h>

char canvas[10000][10000];
void initCanvas(int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            canvas[i][j] = ' ';
        }
    }
}

void fra(int n, int x, int y)
{
    int size = pow(3, n - 2);
    if (n == 1)
    {
        canvas[x][y] = 'X';
        return;
    }
    fra(n - 1, x, y);
    fra(n - 1, x + 2 * size, y);
    fra(n - 1, x + size, y + size);
    fra(n - 1, x, y + 2 * size);
    fra(n - 1, x + 2 * size, y + 2 * size);
}

int main()
{
    int n;
    scanf("%d", &n);
    int size = pow(3, n - 1);
    initCanvas(size);
    fra(n, 0, 0);
    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }

    return 0;
}

// https://blog.csdn.net/mili_j/article/details/130273454
// https://zhuanlan.zhihu.com/p/277523719?utm_psn=1839293756580425728