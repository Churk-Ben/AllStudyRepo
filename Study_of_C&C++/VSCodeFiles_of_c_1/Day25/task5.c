#include <stdio.h>
#define N 100

// ��������
void input(int x[][N], int n);
void output(int x[][N], int n);
// ����rotate_to_right����
void rotate_to_right(int x[][N], int n);

int main()
{
    int x[N][N];
    int n;

    printf("����n: ");
    scanf("%d", &n);
    input(x, n);

    printf("ԭʼ����:\n");
    output(x, n);

    // ����rotate_to_right����
    rotate_to_right(x, n);

    printf("�任�����:\n");
    output(x, n);

    return 0;
}

// ��������
// ����: ����һ��n*n�ľ���x
void input(int x[][N], int n)
{
    int i, j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
            scanf("%d", &x[i][j]);
    }
}

// ��������
// ����: ���һ��n*n�ľ���x
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

// ����rotate_to_right����
// ����: ��һ��n*n�ľ���x��ÿһ��������, ���ұ߱��Ƴ�ȥ��һ���ƻ����
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