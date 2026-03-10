#include <stdio.h>

void bubble_sort(int n, int arr[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int nums[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &nums[i]);
    }

    bubble_sort(n, nums);

    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
        {
            printf("%d\n", nums[i]);
        }
        else
        {
            printf("%d ", nums[i]);
        }
    }

    return 0;
}
