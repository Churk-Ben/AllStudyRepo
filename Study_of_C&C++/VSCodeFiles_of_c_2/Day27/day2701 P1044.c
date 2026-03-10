#include <stdio.h>

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main()
{
    int sing[10], doub[10];
    for (int i = 0, j = 0; i + j < 10;)
    {
        int num = 0;
        scanf("%d", &num);
        if (num % 2 == 0)
        {
            doub[j] = num;
            j++;
        }
        else
        {
            sing[i] = num;
            i++;
        }
    }
    bubbleSort(sing, 5);
    bubbleSort(doub, 5);
    for (int i = 4; i >= 0; i--)
    {
        printf("%d ", sing[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", doub[i]);
    }
    printf("\n");
    return 0;
}
