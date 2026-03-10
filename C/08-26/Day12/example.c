#include <stdio.h>

#define MAX_SIZE 10 // 矩阵的最大尺寸

// 函数声明
int determinant(int matrix[MAX_SIZE][MAX_SIZE], int n);
void getMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n);
void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n);

int main()
{
    int matrix[MAX_SIZE][MAX_SIZE];
    int n;

    printf("请输入矩阵的大小（n x n）：");
    scanf("%d", &n);

    if (n > MAX_SIZE)
    {
        printf("矩阵的大小不能超过 %d\n", MAX_SIZE);
        return 1;
    }

    printf("请输入矩阵的元素：\n");
    getMatrix(matrix, n);

    // printf("输入的矩阵为：\n");
    // printMatrix(matrix, n);

    int det = determinant(matrix, n);
    printf("矩阵的行列式为：%d\n", det);

    return 0;
}

// 计算行列式的函数
int determinant(int matrix[MAX_SIZE][MAX_SIZE], int n)
{
    int det = 0;

    if (n == 1)
    {
        return matrix[0][0];
    }

    if (n == 2)
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    int submatrix[MAX_SIZE][MAX_SIZE];

    for (int x = 0; x < n; x++)
    {
        int subi = 0; // 子矩阵的行索引
        for (int i = 1; i < n; i++)
        {
            int subj = 0; // 子矩阵的列索引
            for (int j = 0; j < n; j++)
            {
                if (j == x)
                    continue; // 跳过当前列
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det += (x % 2 == 0 ? 1 : -1) * matrix[0][x] * determinant(submatrix, n - 1);
    }

    return det;
}

// 输入矩阵元素的函数
void getMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// 打印矩阵的函数
void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
