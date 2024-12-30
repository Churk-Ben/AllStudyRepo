#include <stdio.h>

int power(int x, int n); // 函数声明

int main()
{
    int x, n;
    int ans;

    while (printf("Enter x and n: "), scanf("%d%d", &x, &n) != EOF)
    {
        ans = power(x, n); // 函数调用
        printf("n = %d, ans = %d\n\n", n, ans);
    }

    return 0;
}

// 函数定义
int power(int x, int n)
{
    int t;

    if (n == 0)
        return 1;
    else if (n % 2)
        return x * power(x, n - 1);
    else
    {
        t = power(x, n / 2);
        return t * t;
    }
}