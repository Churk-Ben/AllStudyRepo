#include <stdio.h>

void bubbleSort(int arr[], int n, int ascending)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if ((ascending && arr[j] > arr[j + 1]) || (!ascending && arr[j] < arr[j + 1]))
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
    int sing[10], doub[10];
    int singCount = 0, doubCount = 0;

    for (int i = 0; i < 10; i++)
    {
        int num;
        scanf("%d", &num);
        
        if (num % 2 == 0)
        {
            doub[doubCount++] = num;
        }
        else
        {
            sing[singCount++] = num;
        }
    }

    bubbleSort(sing, singCount, 0);
    bubbleSort(doub, doubCount, 1);

    for (int i = 0; i < singCount; i++)
    {
        printf("%d ", sing[i]);
    }
    for (int i = 0; i < doubCount; i++)
    {
        printf("%d ", doub[i]);
    }
    printf("\n");

    return 0;
}
