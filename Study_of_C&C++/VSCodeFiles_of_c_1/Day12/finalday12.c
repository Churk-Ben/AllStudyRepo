#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 递归生成全排列
void permute(int *arr, int start, int end, int **matrix)
{
    if (start == end)
    {
        // 输出当前排列
        for (int i = 0; i <= end; i++)
        {
            printf("%d ", matrix[i][arr[i]]);
        }
        printf("\n"); // 换行输出 1

        int inversions = countInversions(arr, end + 1);
        printf("逆序数的数量是: %d\n", inversions);// 输出逆序数
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