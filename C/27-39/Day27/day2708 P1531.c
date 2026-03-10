#include <stdio.h>
#include <string.h>

void sortText(char text[][100], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(text[j], text[j + 1]) > 0)
            {
                char temp[100];
                strcpy(temp, text[j]);
                strcpy(text[j], text[j + 1]);
                strcpy(text[j + 1], temp);
            }
        }
    }
}

void getText(char text[][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        fgets(text[i], 100, stdin);
        text[i][strcspn(text[i], "\n")] = '\0';
    }
}

int main()
{
    char text[10][100];
    int n;
    scanf("%d", &n);
    getchar();
    getText(text, n);
    sortText(text, n);
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", text[i]);
    }
    return 0;
}