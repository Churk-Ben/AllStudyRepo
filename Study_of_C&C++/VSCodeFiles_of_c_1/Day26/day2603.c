#include <stdio.h>
#include <string.h>

void sortNames(char names[][20], int n)
{
    char temp[20];
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(names[i], names[j]) > 0)
            {
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }
}

void getNames(char names[][20], int n) {
    for (int i = 0; i < n; i++)
    {
        scanf("%s", names[i]);
    }
}

void printNames(char names[][20], int n) {
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", names[i]);
    }
}

int main()
{
    char names[10][20];
    int n;

    scanf("%d", &n);

    getNames(names, n);

    sortNames(names, n);

    printNames(names, n);

    return 0;
}
