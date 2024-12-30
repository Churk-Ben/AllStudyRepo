#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// ����������
int countInversions(int arr[], int n)
{
    int cnt = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                cnt++;
            }
        }
    }
    return cnt;
}

// ��������Ԫ�ص�ֵ
void swap(int *pa, int *pb)
{
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

// �ݹ�����ȫ����
void permute(int *arr, int start, int end)
{
    if (start == end)
    {
        // �����ǰ����
        for (int i = 0; i <= end; i++)
        {
            for (int j = 0; i <= end; j++)
            {
                printf("%d ", arr[i]); // 2
            }
        }
        printf("\n"); // ������� 1

        int inversions = countInversions(arr, end + 1);
        printf("��������������: %d\n", inversions);// ���������
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            // ������ǰԪ�غ���ʼԪ��
            swap((arr + start), (arr + i));
            // �ݹ���ã��̶���ǰԪ�أ���ʣ��Ԫ�ؽ�������
            permute(arr, start + 1, end);
            // ���ݣ���Ԫ�ؽ����������Ա���һ��ѭ��ʹ��
            swap((arr + start), (arr + i));
        }
    }
}

int main()
{
    int n;
    printf("n: ");
    scanf("%d", &n);
    double c[n][n];                            // �������
    int *arr = (int *)malloc(n * sizeof(int)); // ����ռ�

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &c[i][j]);
        }
    }

    printf("The matrix is:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2lf ", c[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    } // ��������Ԫ��

    permute(arr, 0, n - 1);

    free(arr); // �ͷſռ�

    return 0;
}