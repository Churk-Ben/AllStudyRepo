#include <stdio.h>

int main() {
    int a[]={5,8,7,6,2,7,3};
    int y,*p=&a[1];

    y=(*--p)++;
    printf("%5d",y);
    printf("%5d\n",a[0]);

    return 0;
}