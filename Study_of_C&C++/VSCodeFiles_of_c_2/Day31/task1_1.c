#include <stdio.h>
#define N 5

void input(int x[], int n);
void output(int x[], int n);
void find_min_max(int x[], int n, int *pmin, int *pmax);

int main() {
    int a[N];
    int min, max;

    printf("¼��%d������:\n", N);
    input(a, N);

    printf("������: \n");
    output(a, N);

    printf("���ݴ���...\n");
    find_min_max(a, N, &min, &max);

    printf("������:\n");
    printf("min = %d, max = %d\n", min, max);

    return 0;
}

void input(int x[], int n) {
    int i;

    for(i = 0; i < n; ++i)
        scanf("%d", &x[i]);
}

void output(int x[], int n) {
    int i;
    
    for(i = 0; i < n; ++i)
        printf("%d ", x[i]);
    printf("\n");
}

void find_min_max(int x[], int n, int *pmin, int *pmax) {
    int i;
    
    *pmin = *pmax = x[0];

    for(i = 0; i < n; ++i)
        if(x[i] < *pmin)
            *pmin = x[i];
        else if(x[i] > *pmax)
            *pmax = x[i];
}