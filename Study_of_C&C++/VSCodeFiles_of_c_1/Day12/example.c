#include <stdio.h>

#define MAX_SIZE 10 // ��������ߴ�

// ��������
int determinant(int matrix[MAX_SIZE][MAX_SIZE], int n);
void getMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n);
void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n);

int main()
{
    int matrix[MAX_SIZE][MAX_SIZE];
    int n;

    printf("���������Ĵ�С��n x n����");
    scanf("%d", &n);

    if (n > MAX_SIZE)
    {
        printf("����Ĵ�С���ܳ��� %d\n", MAX_SIZE);
        return 1;
    }

    printf("����������Ԫ�أ�\n");
    getMatrix(matrix, n);

    // printf("����ľ���Ϊ��\n");
    // printMatrix(matrix, n);

    int det = determinant(matrix, n);
    printf("���������ʽΪ��%d\n", det);

    return 0;
}

// ��������ʽ�ĺ���
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
        int subi = 0; // �Ӿ����������
        for (int i = 1; i < n; i++)
        {
            int subj = 0; // �Ӿ����������
            for (int j = 0; j < n; j++)
            {
                if (j == x)
                    continue; // ������ǰ��
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det += (x % 2 == 0 ? 1 : -1) * matrix[0][x] * determinant(submatrix, n - 1);
    }

    return det;
}

// �������Ԫ�صĺ���
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

// ��ӡ����ĺ���
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
