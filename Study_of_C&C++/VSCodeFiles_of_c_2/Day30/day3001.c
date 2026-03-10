#include <stdio.h>

int main() {
    struct abc {
        int a;
        char b;
        float c;
    } my_struct1,my_struct2;

    my_struct1.a = 10;
    my_struct1.b = 'A';
    my_struct1.c = 3.14;

    printf("a = %d\n", my_struct1.a);
    printf("b = %c\n", my_struct1.b);
    printf("c = %f\n", my_struct1.c);

    return 0;
}

