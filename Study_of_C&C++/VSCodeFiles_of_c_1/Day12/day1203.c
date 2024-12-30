#include <stdio.h>
#include <stdlib.h>

// 交换两个元素的值
void swap(int *pa, int *pb)
{
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

// 递归生成全排列
void permute(int *arr, int start, int end)
{
    if (start == end)
    {
        // 输出当前排列
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
            // 交换当前元素和起始元素
            swap((arr + start), (arr + i));
            // 递归调用，固定当前元素，对剩余元素进行排列
            permute(arr, start + 1, end);
            // 回溯，将元素交换回来，以便下一次循环使用
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
    }// 输入数组元素

    permute(arr, 0, n - 1);

    free(arr);
    return 0;
}