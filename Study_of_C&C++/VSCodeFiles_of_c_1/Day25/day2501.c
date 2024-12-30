#include <stdio.h>
#define N 100

// 函数声明
void input(int x[][N], int n);
void output(int x[][N], int n);
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

    // 调用 rotate_to_right 函数
    rotate_to_right(x, n); // 添加调用

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

void rotate_to_right(int x[][N], int n)
{
    int i, j;
    int temp[N];

    for (i = 0; i < n; ++i)
    {
        temp[i] = x[i][n - 1];
    }

    for (j = n - 1; j > 0; --j)
    {
        for (i = 0; i < n; ++i)
        {
            x[i][j] = x[i][j - 1];
        }
    }

    for (i = 0; i < n; ++i)
    {
        x[i][0] = temp[i];
    }
}
