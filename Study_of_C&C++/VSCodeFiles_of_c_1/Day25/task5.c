#include <stdio.h>
#define N 100

// 函数声明
void input(int x[][N], int n);
void output(int x[][N], int n);
// 函数rotate_to_right声明
void rotate_to_right(int x[][N], int n);

int main()
{
    int x[N][N];
    int n;

    printf("输入n: ");
    scanf("%d", &n);
    input(x, n);

    printf("原始矩阵:\n");
    output(x, n);

    // 函数rotate_to_right调用
    rotate_to_right(x, n);

    printf("变换后矩阵:\n");
    output(x, n);

    return 0;
}

// 函数定义
// 功能: 输入一个n*n的矩阵x
void input(int x[][N], int n)
{
    int i, j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
            scanf("%d", &x[i][j]);
    }
}

// 函数定义
// 功能: 输出一个n*n的矩阵x
void output(int x[][N], int n)
{
    int i, j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
            printf("%4d", x[i][j]);

        printf("\n");
    }
}

// 函数rotate_to_right定义
// 功能: 把一个n*n的矩阵x，每一列向右移, 最右边被移出去的一列绕回左边
void rotate_to_right(int x[][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        int temp = x[i][n - 1];
        for (int j = n - 1; j > 0; j--)
        {
            x[i][j] = x[i][j - 1];
        }
        x[i][0] = temp;
    }
}