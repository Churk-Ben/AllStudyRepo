#include <stdio.h>

#define MAX 10 // �����������ά��Ϊ10

void multiplyMatrices(int first[MAX][MAX], int second[MAX][MAX], int result[MAX][MAX], int rowFirst, int columnFirst, int rowSecond, int columnSecond) {
    // ��ʼ���������Ϊ0
    for (int i = 0; i < rowFirst; i++) {
        for (int j = 0; j < columnSecond; j++) {
            result[i][j] = 0;
        }
    }

    // ����˷�
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

    // �����һ�������ά��
    printf("�������һ�����������������: ");
    scanf("%d %d", &rowFirst, &columnFirst);

    // �����һ������
    printf("�������һ�������Ԫ��:\n");
    for (int i = 0; i < rowFirst; i++) {
        for (int j = 0; j < columnFirst; j++) {
            scanf("%d", &first[i][j]);
        }
    }

    // ����ڶ��������ά��
    printf("������ڶ������������������: ");
    scanf("%d %d", &rowSecond, &columnSecond);

    // ����Ƿ���Խ��г˷�
    if (columnFirst != rowSecond) {
        printf("����˷��޷����У�������������ƥ�䡣\n");
        return 1;
    }

    // ����ڶ�������
    printf("������ڶ��������Ԫ��:\n");
    for (int i = 0; i < rowSecond; i++) {
        for (int j = 0; j < columnSecond; j++) {
            scanf("%d", &second[i][j]);
        }
    }

    // ���о���˷�
    multiplyMatrices(first, second, result, rowFirst, columnFirst, rowSecond, columnSecond);

    // ����������
    printf("�������:\n");
    printMatrix(result, rowFirst, columnSecond);

    return 0;
}
