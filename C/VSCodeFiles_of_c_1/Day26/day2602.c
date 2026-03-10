#include <stdio.h>

void size(int an[]);

int main()
{
    int an[4] = {1, 2, 3, 4};
    int n = sizeof(an);
    printf("%d\n", n);
    size(an);
    return 0;
}

void size(int an[])
{
    printf("%d\n", sizeof(an));
}
