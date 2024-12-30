#include <stdio.h>
#include <math.h>

char fractal_universe[10000][10000];

void fra_universe(int x, int y, int n) // n表示是几度的分形宇宙，（x，y）表示n度分形宇宙的左上角的坐标；
{
    int distance = pow(3, n - 2);
    if (n == 1)
    {
        fractal_universe[x][y] = 'X';
        return;
    }
    fra_universe(x, y, n - 1); // （x，y）表示n度的分形宇宙图形的左上角的n-1度分形宇宙图形的左上角坐标

    fra_universe(x + 2 * distance, y, n - 1); // （x + 2 * distance,y）表示n度的分形宇宙图形的右上角的n-1度分形宇宙图形的左上角的坐标；

    fra_universe(x + distance, y + distance, n - 1); // （x + distance, y + distance）表示n度的分形宇宙图形的中间的n-1度分形宇宙图形的左上角坐标

    fra_universe(x, y + 2 * distance, n - 1); //(x, y + 2 * distance)表示n度的分形宇宙图形的左下角的n-1度的分形宇宙图形的左上角的坐标

    fra_universe(x + 2 * distance, y + 2 * distance, n - 1); // （x + 2 * distance, y + 2 * distance）表示n度的分形宇宙图形的右下角的n-1度分形宇宙图形的左上角坐标
}

int main()
{
    int n;
    scanf("%d", &n);
    int size = pow(3, n - 1);
    fra_universe(0, 0, n);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (fractal_universe[i][j] != 'X')
            {
                fractal_universe[i][j] = ' ';
            }
            printf("%c", fractal_universe[i][j]);
        }
        printf("\n");
    }

    return 0;
}

//https://blog.csdn.net/mili_j/article/details/130273454