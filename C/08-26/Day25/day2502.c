#include <stdio.h>

void bubble_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
}

int is_the_num(int num)
{
    int a = num * num;
    int b = num * num * num;
    int s[15], i;

    i = 0;
    while (a)
    {
        s[i] = a % 10;
        a /= 10;
        i++;
    }
    while (b)
    {
        s[i] = b % 10;
        b /= 10;
        i++;
    }
    if (i != 10)
        return 0;

    bubble_sort(s, i);

    for (int j = 0; j < 10; j++)
        if (s[j] != j)
            return 0;

    return 1;
}

int main()
{
    for (int i = 40; i <= 100; i++)
    {
        if (is_the_num(i))
        {
            printf("%d\n", i);
        }
    }
    return 0;
}