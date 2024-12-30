#include <stdio.h>

enum
{
    MAX_SIZE = 100
};

void bubbleSort(int n, int arr[])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void printArray(int n, int nums[])
{
    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
            printf("%d\n", nums[i]);
        else
            printf("%d ", nums[i]);
    }
}

int main()
{
    int n, nums[MAX_SIZE];
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    bubbleSort(n, nums);

    printArray(n, nums);
    return 0;
}