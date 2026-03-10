#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    char ch;
    int character = 0;
    int line = 0;

    fp = fopen("data4.txt", "r");
    if (fp == NULL)
    {
        printf("File no found\n");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
            line++;
        if (ch != ' ' && ch != '\n' && ch != '\t')
            character++;
    }

    if (ftell > 0 && ch != '\n')
        line++;

    printf("Total lines: %d\n", line);
    printf("Total characters: %d\n", character);

    fclose(fp);
    return 0;
}
