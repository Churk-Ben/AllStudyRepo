#include <stdio.h>

void bubble_sort(int arr[], int n)
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
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    bubble_sort(a, n);

    for (int i = n - 1; i >= 0; i--)
    {
        if (a[i] < 70)
        {
            break;
        }
        printf("%d\n", a[i]);
    }

    return 0;
}
