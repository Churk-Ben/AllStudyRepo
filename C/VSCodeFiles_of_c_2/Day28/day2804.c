#include <stdio.h>

char x[100][20001];
int main()
{
    int index[100];
    int n, t, temp;
    int j, k;
    scanf("%d%d", &n, &t);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", x[i]);
        index[i] = i;
    }
    for (int i = 0; i < t; i++)
    {
        scanf("%d%d", &j, &k);
        temp = index[j - 1];
        index[j - 1] = index[k - 1];
        index[k - 1] = temp;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", x[index[i]]);
    }

    return 0;
}