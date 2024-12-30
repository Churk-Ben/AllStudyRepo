#include <stdio.h>
#include <stdlib.h>

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
            printf("%d ", arr[i]);
        }
        printf("\n");
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
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }// ��������Ԫ��

    permute(arr, 0, n - 1);

    free(arr);
    return 0;
}