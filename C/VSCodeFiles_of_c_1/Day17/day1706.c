#include <stdio.h>

int main()
{
    int n, k;

        scanf("%d", &n);
        scanf("%d", &k);
        int a[n];
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }

        for (int i = 0; i < n; i++)
        {
            printf("%d\n", a[k]);
            k++;
            k %= n;
        }
    

    return 0;
}
