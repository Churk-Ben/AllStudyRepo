#include <stdio.h>

void read();
void write();

int main()
{
    write();
    read();
    return 0;
}

void read()
{
    char str[100];
    FILE *fp;
    fp = fopen("..\\file.txt", "r");
    if (fp == NULL)
    {
        printf("Error! Cannot open file.\n");
        return;
    }
    fgets(str, sizeof(str), fp);
    puts(str);
    fclose(fp);
}

void write()
{
    char str[100] = "Hello Worlddddddd";
    FILE *fp;
    fp = fopen("..\\file.txt", "w");
    if (fp == NULL)
    {
        printf("Error! Cannot open file.\n");
        return;
    }
    fputs(str, fp);
    fclose(fp);
}