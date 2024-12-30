#include <stdio.h>

int main()
{
    int n, sum, input, i;
    float avg;
    while (scanf("%d", &n) != EOF)
    {
        sum = 0;
        input = 0;
        i = n;
        while (n--)
        {
            scanf("%d", &input);
            sum += input;
        }
        avg = (float)sum / i;

        printf("%.2f\n", avg);
    }

    return 0;
}