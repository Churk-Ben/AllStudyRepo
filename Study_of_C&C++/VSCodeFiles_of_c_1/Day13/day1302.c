#include <stdio.h>

int main()
{
    float input;
    float sum = 0, max = 0, min = 100;
    printf("Enter expense (-1 to stop):\n");
    for (int i = 0; scanf("%f", &input) && input != -1; i++)
    {
        sum += input;
        if (input > max)
            max = input;
        if (input < min)
            min = input;
    }

    printf("Today's total expense:%.1f\nToday's biggest expense:%.1f\nToday's smallest expense:%.1f\n", sum, max, min);

    return 0;
}