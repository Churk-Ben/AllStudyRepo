#include <stdio.h>
#include <string.h>
int main()
{
    char *ss = "hello world";
    printf("%d\n", (int)strlen(ss));
    printf("%d\n", (int)strlen("ss"));
    return 0;
}