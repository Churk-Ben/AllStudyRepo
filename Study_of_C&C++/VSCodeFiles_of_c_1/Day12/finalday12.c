#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// �ݹ�����ȫ����
void permute(int *arr, int start, int end, int **matrix)
{
    if (start == end)
    {
        // �����ǰ����
        for (int i = 0; i <= end; i++)
        {
            printf("%d ", matrix[i][arr[i]]);
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