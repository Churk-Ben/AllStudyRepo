#include <stdio.h>

enum
{
    M = 100
};

int main()
{
    int x[M];
    int aotoaman = 0, surperman = 0;

    int n, k = 0;
    scanf("%d", &n);

    int l = n - 1;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x[i]);
    }
    while (k != l + 1)
    {
        if (aotoaman >= surperman)
        {
            surperman += x[k++];
        }
        else if (aotoaman < surperman)
        {
            aotoaman += x[l--];
        }
    }
    printf("%d %d", surperman, aotoaman);

    return 0;
}