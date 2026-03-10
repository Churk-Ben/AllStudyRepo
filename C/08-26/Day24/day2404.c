#include <stdio.h>

int main() {
    int n, t, max=0;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &t);
        if(t>max)
            max=t;
    }
    printf("%d", max);
    return 0;
}