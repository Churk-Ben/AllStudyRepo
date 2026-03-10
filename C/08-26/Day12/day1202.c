#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 计算逆序数
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
            for (int j = 0; i <= end; j++)
            {
                printf("%d ", arr[i]); // 2
            }
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

int main()
{
    int n;
    printf("n: ");
    scanf("%d", &n);
    double c[n][n];                            // 定义矩阵
    int *arr = (int *)malloc(n * sizeof(int)); // 申请空间

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
    } // 输入数组元素

    permute(arr, 0, n - 1);

    free(arr); // 释放空间

    return 0;
}