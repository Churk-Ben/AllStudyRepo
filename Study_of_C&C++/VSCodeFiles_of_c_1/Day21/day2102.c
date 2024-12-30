#include <stdio.h>

int main() {
    int a[3]={1,2,3};
    printf("%p\n",a[0]);
    printf("%d\n",a[4]);//它是完全不查啊
    return 0;   
}