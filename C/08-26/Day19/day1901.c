#include <stdio.h>

int main() {
    int a = 1;
    int b = 2;
    int c = 3;
    if(a<c) b=a,a=c,c=b;
    printf("%d",c);
    return 0;
}

