#include <stdio.h>

void printInfo(long long int info[][3], int m, int n)
{
    for (int i = 0; i < n; i++)
        if (m == (int)info[i][1])
            printf("%lld %lld\n", info[i][0], info[i][2]);
}

int main()
{
    int n;
    scanf("%d", &n);
    long long int info[10][3];
    for (int i = 0; i < n; i++)
        scanf("%lld %lld %lld", &info[i][0], &info[i][1], &info[i][2]);
    int m;
    scanf("%d", &m);
    int query[10];
    for (int i = 0; i < m; i++)
        scanf("%d", &query[i]);
    for (int i = 0; i < m; i++)
        printInfo(info, query[i], n);

    return 0;
}