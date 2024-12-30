#include <stdio.h>
#include <string.h>
#define N 100

void sortText(char *str[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(str[j], str[j + 1]) > 0)
            {
                char temp[100];
                strcpy(temp, str[j]);
                strcpy(str[j], str[j + 1]);
                strcpy(str[j + 1], temp);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    char *str[N];
    int n = argc - 1;
    for (int i = 1; i < argc; i++)
    {
        str[i - 1] = argv[i];
    }
    sortText(str, n);
    for (int i = 0; i < n; i++)
    {
        printf("hello, %s\n", str[i]);
    }

    return 0;
}