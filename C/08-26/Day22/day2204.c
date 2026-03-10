#include <stdio.h>

int main() {
    long int arr[40];
    arr[0] = 1;
    arr[1] = 1;

    for (int i = 2; i < 40; i++)
    {
        arr[i] = arr[i-1] + arr[i-2];
    }

    int t=0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%10ld", arr[t]);
            t++;
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}
    