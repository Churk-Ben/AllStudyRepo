#include <stdio.h>

#define MAX 10 // 假设矩阵的最大维度为10

void multiplyMatrices(int first[MAX][MAX], int second[MAX][MAX], int result[MAX][MAX], int rowFirst, int columnFirst, int rowSecond, int columnSecond) {
    // 初始化结果矩阵为0
    for (int i = 0; i < rowFirst; i++) {
        for (int j = 0; j < columnSecond; j++) {
            result[i][j] = 0;
        }
    }

    // 矩阵乘法
    for (int i = 0; i < rowFirst; i++) {
        for (int j = 0; j < columnSecond; j++) {
            for (int k = 0; k < columnFirst; k++) {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
    }
}

void printMatrix(int matrix[MAX][MAX], int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int first[MAX][MAX], second[MAX][MAX], result[MAX][MAX];
    int rowFirst, columnFirst, rowSecond, columnSecond;

    // 输入第一个矩阵的维度
    printf("请输入第一个矩阵的行数和列数: ");
    scanf("%d %d", &rowFirst, &columnFirst);

    // 输入第一个矩阵
    printf("请输入第一个矩阵的元素:\n");
    for (int i = 0; i < rowFirst; i++) {
        for (int j = 0; j < columnFirst; j++) {
            scanf("%d", &first[i][j]);
        }
    }

    // 输入第二个矩阵的维度
    printf("请输入第二个矩阵的行数和列数: ");
    scanf("%d %d", &rowSecond, &columnSecond);

    // 检查是否可以进行乘法
    if (columnFirst != rowSecond) {
        printf("矩阵乘法无法进行，列数和行数不匹配。\n");
        return 1;
    }

    // 输入第二个矩阵
    printf("请输入第二个矩阵的元素:\n");
    for (int i = 0; i < rowSecond; i++) {
        for (int j = 0; j < columnSecond; j++) {
            scanf("%d", &second[i][j]);
        }
    }

    // 进行矩阵乘法
    multiplyMatrices(first, second, result, rowFirst, columnFirst, rowSecond, columnSecond);

    // 输出结果矩阵
    printf("结果矩阵:\n");
    printMatrix(result, rowFirst, columnSecond);

    return 0;
}
