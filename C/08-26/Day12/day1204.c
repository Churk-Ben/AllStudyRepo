#include <stdio.h>
int max(int n, int m)
{
    return (n > m) ? n : m;
}
int min(int n, int m)
{
    return (n < m) ? n : m;
}

int main()
{
    int i, input, n, q, w, e, p = 0;
    float average;
    for (i = 0; scanf("%d", &input) && input != -1; i++)
    {
        scanf("%d", &n);
        q = n;
        e = max(n, q);
        w = min(n, q);
        p = p + n;
    }
    average = p / i;
    printf("%d\n", i);
    printf("%d\n", e);
    printf("%d\n", w);
    printf("%.1f", average);

    return 0;
}