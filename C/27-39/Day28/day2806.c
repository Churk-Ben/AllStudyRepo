#include <stdio.h>

void sort(int s[], int e[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (s[j] > s[j + 1])
            {
                int temps = s[j];
                int tempe = e[j];
                s[j] = s[j + 1];
                e[j] = e[j + 1];
                s[j + 1] = temps;
                e[j + 1] = tempe;
            }
}

void merge(int s[], int e[], int n)
{
    int start = s[0], end = e[0];
    for (int i = 1; i < n; i++)
    {
        if (end < s[i])
        {
            printf("%d %d\n", start, end);
            start = s[i];
            end = e[i];
        }
        else if (end < e[i])
        {
            end = e[i];
        }
    }
    printf("%d %d\n", start, end);
}

int main()
{
    int n;
    scanf("%d", &n);
    int s[n], e[n];
    for (int i = 0; i < n; i++) scanf("%d %d", &s[i], &e[i]);
    sort(s, e, n);
    merge(s, e, n);

    return 0;
}
