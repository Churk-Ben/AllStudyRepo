#include <stdio.h>
#include <string.h>

int main()
{
    char str[500][500];
    size_t max = 0;
    size_t min = 500;
    char y[100][500], z[100][500];
    int i = 0;
    while (1)
    {
        scanf("%s", str[i]);
        i++;
        if (getchar() == '\n')
            break;
    }
    for (int j = 0; j < i; j++)
    {

        if (strlen(str[j]) > max)
        {
            max = strlen(str[j]);
            strcpy(y[0], str[j]);
        }
        if (strlen(str[j]) < min)
        {
            min = strlen(str[j]);
            strcpy(z[0], str[j]);
        }
    }
    printf("%s\n", y[0]);
    printf("%s\n", z[0]);
    return 0;
}