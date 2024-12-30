#include <stdio.h>
#define N 5

void input(int x[], int n);
void output(int x[], int n);
int *find_max(int x[], int n);

int main()
{
    int a[N];
    int *pmax;

    printf("¼��%d������:\n", N);
    input(a, N);

    printf("������: \n");
    output(a, N);

    printf("���ݴ���...\n");
    pmax = find_max(a, N);

    printf("������:\n");
    printf("max = %d\n", *pmax);

    return 0;
}

void input(int x[], int n)
{
    int i;

    for (i = 0; i < n; ++i)
        scanf("%d", &x[i]);
}

void output(int x[], int n)
{
    int i;

    for (i = 0; i < n; ++i)
        printf("%d ", x[i]);
    printf("\n");
}

int *find_max(int x[], int n)
{
    int *ptr = &x[0];
    int i;
    for (i = 1; i < n; ++i)
        if (x[i] > *ptr)
            ptr = &x[i];
    return ptr;
}