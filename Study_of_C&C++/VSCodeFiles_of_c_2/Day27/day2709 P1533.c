#include <stdio.h>
#include <string.h>

int main()
{
    char str1[10000], str2[10000];
    int lock = 0, j = 0;
    fgets(str1, 10000, stdin);
    for (int i = 0; i < strlen(str1); i++)
    {
        if (str1[i] == '*' && lock == 1)
        {
            continue;
        }
        if (str1[i] != '*' && lock == 0)
        {
            lock = 1;
        }
        str2[j++] = str1[i];
    }
    str2[j] = '\0';
    printf("%s", str2);
    return 0;
}