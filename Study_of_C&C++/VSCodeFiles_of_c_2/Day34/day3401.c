#include <stdio.h>

int main()
{
    char str[] = "Hello World";
    int test[] = {1, 2, 3, 4, 5};

    char *pstr;
    pstr = str;
    int *ptest = test;
    
    printf("String: %s\n", pstr);
    printf("Char: %c\n", *pstr);
    printf("Array: %d\n", *ptest);
    return 0;
}