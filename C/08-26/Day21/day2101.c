#include <stdio.h>

enum {
    SIZE = 500,
    MAX_SIZE = 1000000
};

int main() {
    int n;
    scanf("%d", &n);
    int a[SIZE];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}