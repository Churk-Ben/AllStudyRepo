#include <stdio.h>

enum{
    N=1000,
};

void input(int a[], int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
}

void output(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int max(int a[], int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

int main() {
    int a[N], n, ans;
    scanf("%d", &n);
    input(a, n);
    ans = max(a, n);
    output(a, n);
    printf("max = %d\n", ans);
    return 0;
}