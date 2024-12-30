#include <stdio.h>

int main()
{
    char str[100] = "Hello World";
    char *ptr = str;

    printf("%s\n\n", str);

    printf("%p\n", str);
    printf("%p\n", ptr);
    printf("%p\n\n", &str[0]);

    printf("%p\n", &str[1]);
    printf("%p\n\n", &str[2]);

    char *strs[] = {"apple", "banana", "orange"};

    printf("%p\n", strs);
    printf("%p\n", &strs[0]);
    printf("%p\n", strs[0]);
    printf("%s\n\n", strs[0]);

    printf("%p\n", &strs[1]);
    printf("%p\n", strs[1]);
    printf("%s\n\n", strs[1]);
    // printf("%s\n", *strs[1]);
    printf("%c\n", *strs[1]);

    return 0;
}