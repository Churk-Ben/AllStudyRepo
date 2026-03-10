#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);

    int a[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }

    int b[N], t = 0;
    for (int i = 0; i < N; i++)
    {
        b[i] = 0;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i != j && a[i] == -a[j] && !b[j])
            {
                t++;
                b[j] = 1;
                break;
            }
        }
    }
    t /= 2;
    printf("%d\n", t);

    return 0;
}
