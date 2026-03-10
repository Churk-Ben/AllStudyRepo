#include <stdio.h>
#include <string.h>

int main()
{
    char str[200], be[200], af[200];
    fgets(str, 200, stdin);
    int len = strlen(str);
    int k;
    scanf("%d", &k);

    strcpy(af, str);
    for (int i = 0; i < k; i++)
    {
        af[i] = af[k];
    }
    strcpy(be, str);
    for (int i = k; i < len - 1; i++)
    {
        be[i] = be[k - 1];
    }
    printf("%s", be);
    printf("%s", af);
    return 0;
}