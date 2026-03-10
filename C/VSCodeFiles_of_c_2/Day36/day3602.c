#include <stdio.h>

int is_gap_year(int year)
{
    if (year % 400 == 0)
        return 1;
    if (year % 100 == 0)
        return 0;
    if (year % 4 == 0)
        return 1;
    return 0;
}

int main()
{
    int cnt = 0;
    for (int i = 1900; i <= 2500; i++)
    {
        if (is_gap_year(i))
        {
            cnt++;
            printf("%d ", i);
            if (cnt % 5 == 0)
                printf("\n");
        }
    }
    return 0;
}
