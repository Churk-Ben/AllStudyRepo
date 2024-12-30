#include <stdio.h>

int len(char str[])
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

int main()
{
    char str[100];
    fgets(str, 100, stdin);

    int k;
    scanf("%d", &k);

    char str1[100],str2[100];

    for (int i = 0; i < k; i++)
    {
        str1[i] = str[i];
    }
    for (int i = k; i < len(str) - 1; i++)
    {
        str1[i] = str[k - 1];
    }
    str1[len(str) - 1] = '\0';

    for (int i = 0; i < k; i++)
    {
        str2[i] = str[k];
    }
    for (int i = k; i < len(str) - 1; i++)
    {
        str2[i] = str[i];
    }
    str2[len(str) - 1] = '\0';

    printf("%s\n", str1);
    printf("%s\n", str2);

    return 0;
}
