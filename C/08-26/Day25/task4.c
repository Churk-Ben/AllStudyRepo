#include <stdio.h>
#define N 100

// 函数声明
void input(int x[], int n);
double median(int x[], int n);

int main()
{
    int x[N];
    int n;
    double ans;

    while (printf("Enter n: "), scanf("%d", &n) != EOF)
    {
        input(x, n);
        ans = median(x, n);
        printf("ans = %g\n\n", ans);
    }

    return 0;
}

// 函数定义
void input(int x[], int n)
{
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
}

double median(int x[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (x[i] > x[j])
            {
                int t = x[i];
                x[i] = x[j];
                x[j] = t;
            }

    return (n % 2 == 0) ? (x[n / 2 - 1] + x[n / 2]) / 2.0 : x[n / 2];
}