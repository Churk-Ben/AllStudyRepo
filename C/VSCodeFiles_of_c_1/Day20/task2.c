#include <stdio.h>

int sum_digits(int n); // 函数声明

int main()
{
    int n;
    int ans;

    while (printf("Enter n: "), scanf("%d", &n) != EOF)
    {
        ans = sum_digits(n); // 函数调用
        printf("n = %d, ans = %d\n\n", n, ans);
    }

    return 0;
}

// 函数定义
int sum_digits(int n)
{
    int ans = 0;

    while (n != 0)
    {
        ans += n % 10;
        n /= 10;
    }

    return ans;
}