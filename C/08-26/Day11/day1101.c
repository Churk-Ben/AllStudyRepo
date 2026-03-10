#include <stdio.h>

int main()
{
    int n, sum, input, j, max, min;
    float avg;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        sum = 0;
        j = 0;
        max = 0;
        min = 100;
        while (1)
        {
            scanf("%d", &input);
            if (input == -1)
            {
                avg = (float)sum / j;
                printf("%d\n", j);
                printf("%d\n", max);
                printf("%d\n", min);
                printf("%.1f\n", avg);
                break;
            }
            else
            {
                j++;
                sum += input;
                if (input > max)
                {
                    max = input;
                }
                if (input < min)
                {
                    min = input;
                }
            }
        }
    }

    return 0;
}
