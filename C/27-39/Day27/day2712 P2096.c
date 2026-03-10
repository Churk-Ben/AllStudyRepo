#include <stdio.h>
#include <math.h>

double avg(int arr[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum / n / 2.0;
}

int main()
{
    char name[10][10];
    int guess[10] = {0};
    double average;
    int n;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%s %d", name[i], &guess[i]);
    }
    
    average = avg(guess, n);

    double min = 100; 
    int record = -1;
    
    for (int i = 0; i < n; i++)
    {
        if (fabs(guess[i] - average) < min)
        {
            min = fabs(guess[i] - average);
            record = i;
        }
    }
    printf("%d %s\n", (int)average, name[record]);
    return 0;
}