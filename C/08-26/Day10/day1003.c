#include <stdio.h>
#include <math.h>

int main() {
    int n;
    long int a;
    double b;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%ld", &a);
        b = sqrt(a);
        if ((int)b==b)
        {
            printf("%d\n", (int)b);
            break;
        }
    }
    
    return 0;
}