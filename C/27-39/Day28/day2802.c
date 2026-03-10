#include <stdio.h>

void test1() {
    int x=42;
    printf("x = %d\n", x);

    int *ptr=&x;
    printf("ptr = %p\n", ptr);
    printf("*ptr = %d\n", *ptr);

    *ptr=100;
    printf("x = %d\n", x);
}

int main() {
    test1();
    return 0;
}