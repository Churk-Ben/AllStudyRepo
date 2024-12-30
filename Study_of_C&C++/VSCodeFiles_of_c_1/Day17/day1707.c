#include <stdio.h>

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    int a[m], b[n];
    for (int i = 0; i < m; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);
    int c[m + n], t = 0, i = 0, j = 0;

    while (i < m && j < n)
    {
        if (a[i] < b[j])
            c[t++] = a[i++];
        else if (a[i] > b[j])
            c[t++] = b[j++];
        else 
        {
            c[t++] = a[i++];
            j++;
        }
    }

    while (i < m) c[t++] = a[i++];
    while (j < n) c[t++] = b[j++];

    for (int s = 0; s < t; s++)
    {
        printf("%d", c[s]);
        if (s < t - 1) 
            printf(" ");
    }
    printf("\n"); 

    return 0;
}
