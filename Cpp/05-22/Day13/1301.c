#include <stdio.h>
#define N 100000

int main()
{
    int n, a[N];
    int flag, cur;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
        if (i == 0)
        {
            flag = a[0];
            cur = 0;
        }
        else if (a[i] != flag)
        {
            flag = a[i];
            a[++cur] = a[i];
        }
    }

    for (int i = 0; i <= cur; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
